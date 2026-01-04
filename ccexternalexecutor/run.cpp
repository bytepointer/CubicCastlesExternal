#include <windows.h>
#include <iostream>
#include <tlhelp32.h>
#include "offsets.h"

#include <thread>
#include <chrono>
//actually just works one game process;

#include <vector>

//GLOBAL VARIABLES
DWORD processBaseAddress;
HANDLE process;

DWORD getGameProcessId() {
	
	DWORD reply = 0;

	wchar_t* processName = L"Cubic.exe";

	PROCESSENTRY32 ps;
	ps.dwSize = sizeof(PROCESSENTRY32);

	//th32cs flag
	//0 identificator

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	
	//snapshot handle
	//PS output
	bool succesfulProcess = Process32First(snapshot, &ps);

	if (succesfulProcess) {
		while (Process32Next(snapshot, &ps)) {
			//wchar_t (same cases)

			if (_wcsicmp(ps.szExeFile, processName) == 0) {
				reply = ps.th32ProcessID;
			}
		}
	}

	CloseHandle(snapshot);
	return reply;
}

DWORD getProcessBaseAddress(DWORD processId) {

	DWORD baseAddress = 0x0;

	MODULEENTRY32 pcs;
	pcs.dwSize = sizeof(MODULEENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);

	if (Module32First(snapshot, &pcs)) {
		baseAddress = (int)pcs.modBaseAddr;
	}

	CloseHandle(snapshot);
	return baseAddress;

}

int readMemory(int address) {

	int memoryValue;
	ReadProcessMemory(process, (LPCVOID)address, &memoryValue, sizeof(memoryValue), nullptr);
	
	return memoryValue;
}

struct data {
	int offset;
	const BYTE* buffer;
	size_t size;
	int type;
	int allocOffset;
};

data getData(std::string type, BOOL status) {

	data reply;

	const BYTE* newBuffer;
	const BYTE* oldBuffer;

	size_t newSize;
	size_t oldSize;

	int packetAddr = processBaseAddress + Offsets::packetSendOffset;

	//CHANGE LATER TYPE TO INTEGER
	if (type == "fly") {
		reply.offset = processBaseAddress + Offsets::flyBaseOffset;
		newBuffer = Offsets::flyBuffer;
		oldBuffer = Offsets::flyOldBuffer;
		reply.type = Offsets::flyType;

		newSize = sizeof(Offsets::flyBuffer);
		oldSize = sizeof(Offsets::flyOldBuffer);
	}

	if (type == "noclip") {

		int teste = processBaseAddress + Offsets::noClipBaseOffset;

		reply.offset = readMemory(processBaseAddress+Offsets::noClipBaseOffset) + Offsets::noClipOffset;
		newBuffer = Offsets::noClipBuffer;
		oldBuffer = Offsets::noClipOldBuffer;

		reply.type = Offsets::noClipType;

		//FAZER VERIFICAR DEPOIS E ARRUMAR EM CADA PRA ECONOMIZAR LINHAS DE CODIGO!
		newSize = sizeof(Offsets::noClipBuffer);
		oldSize = sizeof(Offsets::noClipOldBuffer);
	}

	if (type == "antiHit") {

		byte* newbuff = new byte[44];

		//int32_t rel32 = processBaseAddress + (0x120D57 - (0x14570 + 5));

		memcpy(newbuff, Offsets::healthAllocBuffer, 44);

		int hitAddr = processBaseAddress + Offsets::healthTypeOffset;

		unsigned char bytesHitAddr[4];
		memcpy(bytesHitAddr, &hitAddr, 4);

		newbuff[3] = bytesHitAddr[0];
		newbuff[4] = bytesHitAddr[1];
		newbuff[5] = bytesHitAddr[2];
		newbuff[6] = bytesHitAddr[3];

		/*int retAddr = packetAddr + 6;

		unsigned char bytesRetAddr[4];
		memcpy(bytesRetAddr, &retAddr, 4);

		newbuff[40] = bytesRetAddr[0];
		newbuff[41] = bytesRetAddr[1];
		newbuff[42] = bytesRetAddr[2];
		newbuff[43] = bytesRetAddr[3];*/

		/*int allocMemoryPlace = processBaseAddress + Offsets::healthAllocatedAddress + 33;

		unsigned char bytesAllocAddr[4];

		memcpy(bytesRetAddr, &allocMemoryPlace, 4);

		newbuff[]*/
		
		//FALTA O JNE ORIGINALCODE

		
		reply.offset = packetAddr;

		reply.allocOffset = processBaseAddress + Offsets::healthAllocatedAddress;

		reply.type = Offsets::healthType;

		newBuffer = newbuff;
		oldBuffer = Offsets::packetSendOldBuffer;

		newSize = sizeof(Offsets::healthAllocBuffer);
		oldSize = sizeof(Offsets::packetSendOldBuffer);
	}

	if (status) {
		reply.buffer = newBuffer;
		reply.size = newSize;
	}
	else {
		reply.buffer = oldBuffer;
		reply.size = oldSize;
		reply.type = 0;
	}

	return reply;
}

void freezeValue(DWORD address, std::atomic<bool>* run, data infoData) {
	
	while (run->load()) {
		bool a = WriteProcessMemory(process, (LPVOID)address, infoData.buffer, infoData.size, nullptr);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

std::shared_ptr<std::atomic<bool>> run(std::string type, bool status) {

	data infoData = getData(type, status);

	int finalAddress = infoData.offset;

	//CHECK IF ALIVE!
	DWORD check_if_alive;

	if (!process) return nullptr;

	GetExitCodeProcess(process, &check_if_alive);

	if (check_if_alive != STILL_ACTIVE) return nullptr;
	
	// CODE

	std::shared_ptr<std::atomic<bool>> runFlag;

	switch (infoData.type) {
	case 0:

		WriteProcessMemory(process, (LPVOID)finalAddress, infoData.buffer, infoData.size, nullptr);
		break;

	case 1:

		runFlag = std::make_shared<std::atomic<bool>>(true);
		std::thread(freezeValue, finalAddress, runFlag.get(), infoData).detach();

		return runFlag;

	case 2:
	
		//alocar memoria

		//LPVOID allocMemory = VirtualAllocEx(process, nullptr, infoData.size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		if (status) {
			WriteProcessMemory(process, (LPVOID)infoData.allocOffset, infoData.buffer, infoData.size, nullptr);

			BYTE jmp[6] = { 0xE9, 0xEE, 0x37, 0xEF, 0xFF, 0x90 };

			WriteProcessMemory(process, (LPVOID)infoData.offset, jmp, sizeof(jmp), nullptr);
		}
		else {
			WriteProcessMemory(process, (LPVOID)infoData.offset, infoData.buffer, infoData.size, nullptr);
		};
		//0xE9 ADDRESS
		break;
	}

	//RETURNS RUNFLAG JUST IF NECESSARY!
	return nullptr;

}

bool gameAttach() {

	DWORD processId = getGameProcessId();

	if (processId == 0) return false;

	process = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_VM_OPERATION, FALSE, processId);

	// i will kill myself becuase 1 hour to note that i did not added "PROCES_VM_READ" flag

	processBaseAddress = getProcessBaseAddress(processId);

	return true;
}
//eu poderia ter botado so um while inicializando as funcoes e tipo verificando se o botao ta ligado mas eu fiz dessa forma pq sla, acho
//q seria "Mais organizado"