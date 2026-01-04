#pragma once

#include "run.h"

std::shared_ptr<std::atomic<bool>> noClipRun;

bool attached = false;

namespace ccexternalexecutor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Sumário para MyForm
	/// </summary>
	public ref class CCExternal : public System::Windows::Forms::Form
	{
	public:
		CCExternal(void)
		{
			InitializeComponent();
			this->Text = "External";
			//
			//TODO: Adicione o código do construtor aqui
			//
		}

	protected:
		/// <summary>
		/// Limpar os recursos que estão sendo usados.
		/// </summary>
		~CCExternal()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Panel^ flyPanel;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ attach;
	private: System::Windows::Forms::Panel^ noClipPanel;
	private: System::Windows::Forms::Label^ outputText;
	private: System::Windows::Forms::Button^ antiKillButt;
	private: System::Windows::Forms::Panel^ antiHitPanel;




		   //CAN BE USED TO FUTURE THINGS LIKE NOCLIP

	protected:

	private:
		/// <summary>
		/// Variável de designer necessária.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necessário para suporte ao Designer - não modifique 
		/// o conteúdo deste método com o editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(CCExternal::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->flyPanel = (gcnew System::Windows::Forms::Panel());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->attach = (gcnew System::Windows::Forms::Button());
			this->noClipPanel = (gcnew System::Windows::Forms::Panel());
			this->outputText = (gcnew System::Windows::Forms::Label());
			this->antiKillButt = (gcnew System::Windows::Forms::Button());
			this->antiHitPanel = (gcnew System::Windows::Forms::Panel());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::Control;
			this->button1->Location = System::Drawing::Point(239, 24);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"fly";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &CCExternal::button1_Click);
			// 
			// flyPanel
			// 
			this->flyPanel->BackColor = System::Drawing::Color::Red;
			this->flyPanel->Location = System::Drawing::Point(351, 24);
			this->flyPanel->Name = L"flyPanel";
			this->flyPanel->Size = System::Drawing::Size(32, 23);
			this->flyPanel->TabIndex = 1;
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::SystemColors::Control;
			this->button2->Location = System::Drawing::Point(239, 75);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 2;
			this->button2->Text = L"no clip";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &CCExternal::button2_Click);
			// 
			// attach
			// 
			this->attach->Location = System::Drawing::Point(12, 24);
			this->attach->Name = L"attach";
			this->attach->Size = System::Drawing::Size(75, 23);
			this->attach->TabIndex = 3;
			this->attach->Text = L"attach";
			this->attach->UseVisualStyleBackColor = true;
			this->attach->Click += gcnew System::EventHandler(this, &CCExternal::attach_Click);
			// 
			// noClipPanel
			// 
			this->noClipPanel->BackColor = System::Drawing::Color::Red;
			this->noClipPanel->Location = System::Drawing::Point(351, 75);
			this->noClipPanel->Name = L"noClipPanel";
			this->noClipPanel->Size = System::Drawing::Size(32, 23);
			this->noClipPanel->TabIndex = 2;
			// 
			// outputText
			// 
			this->outputText->AutoSize = true;
			this->outputText->BackColor = System::Drawing::Color::Transparent;
			this->outputText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->outputText->ForeColor = System::Drawing::Color::ForestGreen;
			this->outputText->Location = System::Drawing::Point(22, 259);
			this->outputText->Name = L"outputText";
			this->outputText->Size = System::Drawing::Size(0, 16);
			this->outputText->TabIndex = 4;
			// 
			// antiKillButt
			// 
			this->antiKillButt->BackColor = System::Drawing::SystemColors::Control;
			this->antiKillButt->Location = System::Drawing::Point(239, 137);
			this->antiKillButt->Name = L"antiKillButt";
			this->antiKillButt->Size = System::Drawing::Size(75, 23);
			this->antiKillButt->TabIndex = 5;
			this->antiKillButt->Text = L"anti hit";
			this->antiKillButt->UseVisualStyleBackColor = false;
			this->antiKillButt->Click += gcnew System::EventHandler(this, &CCExternal::noClipButt_Click);
			// 
			// antiHitPanel
			// 
			this->antiHitPanel->BackColor = System::Drawing::Color::Red;
			this->antiHitPanel->Location = System::Drawing::Point(351, 137);
			this->antiHitPanel->Name = L"antiHitPanel";
			this->antiHitPanel->Size = System::Drawing::Size(32, 23);
			this->antiHitPanel->TabIndex = 6;
			// 
			// CCExternal
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(414, 296);
			this->Controls->Add(this->antiHitPanel);
			this->Controls->Add(this->antiKillButt);
			this->Controls->Add(this->outputText);
			this->Controls->Add(this->noClipPanel);
			this->Controls->Add(this->attach);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->flyPanel);
			this->Controls->Add(this->button1);
			this->Name = L"CCExternal";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &CCExternal::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: bool buttonEnabled(System::String^ buttonName) {

		array<Control^>^ control = this->Controls->Find(buttonName, true);

		if (!attached) {
			this->outputText->Text = "Not Attached!";
			return false;
		}

		if (control->Length == 0) return false;

		Panel^ pnl = dynamic_cast<Panel^>(control[0]);

		if (pnl ->BackColor == Color::Green) {

			//ALREADY MAKING THE BUTTON CONVERTION BECAUSE FOR SURE WAS CLICKED

			pnl->BackColor = Color::Red;
			
			//SENDING THAT BACK COLOR WAS GREEN
			return true;
		}
		else {

			// ...
			pnl->BackColor = Color::Green;

			// ...
			return false;
		}
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		run("fly", !buttonEnabled("flyPanel"));

	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {

		if (!buttonEnabled("noClipPanel")) {
			noClipRun = run("noclip", true);
		}
		else {
			noClipRun->store(false);
			run("noclip", false);
		}
	}
private: System::Void attach_Click(System::Object^ sender, System::EventArgs^ e) {

		attached = gameAttach();
		
		if (attached) {
			this->outputText->Text = "Attached!";
		}
		else {
			this->outputText->Text = "Process not open!";
		}

}
private: System::Void noClipButt_Click(System::Object^ sender, System::EventArgs^ e) {

		run("antiHit", !buttonEnabled("antiHitPanel"));
}
private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
};
}
