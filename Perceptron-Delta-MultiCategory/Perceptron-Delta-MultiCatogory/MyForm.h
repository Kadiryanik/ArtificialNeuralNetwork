#pragma once
#include "AnnPoints.h"
#include "AnnMatrix.h"

#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

#define PICTURE_BOX_SIZE 351
#define PICTURE_BOX_SIZE_DIV_TWO 175

#define ZOOM 50

#define BIAS 1
#define EPSILON 0.1

#define PRINT_FREQ 100

#define LEARNING_RATE_PERCEPTRON 0.2
#define LEARNING_RATE_DELTA 0.8

namespace PerceptronDeltaMultiCatogory {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBoxCoordinate;
	private: System::Windows::Forms::GroupBox^  groupBoxClass;
	private: System::Windows::Forms::RadioButton^  radioButtonClassOne;
	private: System::Windows::Forms::RadioButton^  radioButtonClassTwo;
	private: System::Windows::Forms::RadioButton^  radioButtonClassThree;
	private: System::Windows::Forms::RadioButton^  radioButtonClassFour;
	private: System::Windows::Forms::RadioButton^  radioButtonClassFive;
	private: System::Windows::Forms::RadioButton^  radioButtonClassSix;
	private: System::Windows::Forms::ComboBox^  comboBoxClassSize;
	private: System::Windows::Forms::RadioButton^  radioButtonFnet1;
	private: System::Windows::Forms::RadioButton^  radioButtonFnet2;
	private: System::Windows::Forms::CheckBox^  checkBoxNormalization;
	private: System::Windows::Forms::Button^  buttonResetPoint;
	private: System::Windows::Forms::Button^  buttonProcess;
	private: System::Windows::Forms::Label^  labelDebug;
	private: System::Windows::Forms::PrintDialog^  printDialog1;


	protected:

	protected:

	private:
		AnnPoints^ refAnnPoints;
		AnnMatrix^ w;
		int classSize;
		int firstCall;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBoxCoordinate = (gcnew System::Windows::Forms::PictureBox());
			this->groupBoxClass = (gcnew System::Windows::Forms::GroupBox());
			this->radioButtonClassOne = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonClassTwo = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonClassThree = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonClassFour = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonClassFive = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonClassSix = (gcnew System::Windows::Forms::RadioButton());
			this->comboBoxClassSize = (gcnew System::Windows::Forms::ComboBox());
			this->radioButtonFnet1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonFnet2 = (gcnew System::Windows::Forms::RadioButton());
			this->checkBoxNormalization = (gcnew System::Windows::Forms::CheckBox());
			this->buttonResetPoint = (gcnew System::Windows::Forms::Button());
			this->buttonProcess = (gcnew System::Windows::Forms::Button());
			this->labelDebug = (gcnew System::Windows::Forms::Label());
			this->printDialog1 = (gcnew System::Windows::Forms::PrintDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxCoordinate))->BeginInit();
			this->groupBoxClass->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBoxCoordinate
			// 
			this->pictureBoxCoordinate->BackColor = System::Drawing::SystemColors::Control;
			this->pictureBoxCoordinate->Location = System::Drawing::Point(12, 12);
			this->pictureBoxCoordinate->Name = L"pictureBoxCoordinate";
			this->pictureBoxCoordinate->Size = System::Drawing::Size(PICTURE_BOX_SIZE, PICTURE_BOX_SIZE);
			this->pictureBoxCoordinate->TabIndex = 0;
			this->pictureBoxCoordinate->TabStop = false;
			this->pictureBoxCoordinate->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pictureBoxCoordinate_Paint);
			this->pictureBoxCoordinate->Click += gcnew System::EventHandler(this, &MyForm::pictureBoxCoordinate_Click);
			// 
			// groupBoxClass
			// 
			this->groupBoxClass->Controls->Add(this->radioButtonClassSix);
			this->groupBoxClass->Controls->Add(this->radioButtonClassFive);
			this->groupBoxClass->Controls->Add(this->radioButtonClassFour);
			this->groupBoxClass->Controls->Add(this->radioButtonClassThree);
			this->groupBoxClass->Controls->Add(this->radioButtonClassTwo);
			this->groupBoxClass->Controls->Add(this->radioButtonClassOne);
			this->groupBoxClass->Location = System::Drawing::Point(404, 6);
			this->groupBoxClass->Name = L"groupBoxClass";
			this->groupBoxClass->Size = System::Drawing::Size(408, 33);
			this->groupBoxClass->TabIndex = 8;
			this->groupBoxClass->TabStop = false;
			// 
			// radioButtonClassOne
			// 
			this->radioButtonClassOne->AutoSize = true;
			this->radioButtonClassOne->Location = System::Drawing::Point(7, 10);
			this->radioButtonClassOne->Name = L"radioButtonClassOne";
			this->radioButtonClassOne->Size = System::Drawing::Size(59, 17);
			this->radioButtonClassOne->TabIndex = 0;
			this->radioButtonClassOne->TabStop = true;
			this->radioButtonClassOne->Text = L"Class 1";
			this->radioButtonClassOne->UseVisualStyleBackColor = true;
			// 
			// radioButtonClassTwo
			// 
			this->radioButtonClassTwo->AutoSize = true;
			this->radioButtonClassTwo->Location = System::Drawing::Point(72, 10);
			this->radioButtonClassTwo->Name = L"radioButtonClassTwo";
			this->radioButtonClassTwo->Size = System::Drawing::Size(59, 17);
			this->radioButtonClassTwo->TabIndex = 1;
			this->radioButtonClassTwo->TabStop = true;
			this->radioButtonClassTwo->Text = L"Class 2";
			this->radioButtonClassTwo->UseVisualStyleBackColor = true;
			// 
			// radioButtonClassThree
			// 
			this->radioButtonClassThree->AutoSize = true;
			this->radioButtonClassThree->Location = System::Drawing::Point(137, 10);
			this->radioButtonClassThree->Name = L"radioButtonClassThree";
			this->radioButtonClassThree->Size = System::Drawing::Size(59, 17);
			this->radioButtonClassThree->TabIndex = 2;
			this->radioButtonClassThree->TabStop = true;
			this->radioButtonClassThree->Text = L"Class 3";
			this->radioButtonClassThree->UseVisualStyleBackColor = true;
			// 
			// radioButtonClassFour
			// 
			this->radioButtonClassFour->AutoSize = true;
			this->radioButtonClassFour->Location = System::Drawing::Point(202, 10);
			this->radioButtonClassFour->Name = L"radioButtonClassFour";
			this->radioButtonClassFour->Size = System::Drawing::Size(59, 17);
			this->radioButtonClassFour->TabIndex = 3;
			this->radioButtonClassFour->TabStop = true;
			this->radioButtonClassFour->Text = L"Class 4";
			this->radioButtonClassFour->UseVisualStyleBackColor = true;
			// 
			// radioButtonClassFive
			// 
			this->radioButtonClassFive->AutoSize = true;
			this->radioButtonClassFive->Location = System::Drawing::Point(267, 10);
			this->radioButtonClassFive->Name = L"radioButtonClassFive";
			this->radioButtonClassFive->Size = System::Drawing::Size(59, 17);
			this->radioButtonClassFive->TabIndex = 4;
			this->radioButtonClassFive->TabStop = true;
			this->radioButtonClassFive->Text = L"Class 5";
			this->radioButtonClassFive->UseVisualStyleBackColor = true;
			// 
			// radioButtonClassSix
			// 
			this->radioButtonClassSix->AutoSize = true;
			this->radioButtonClassSix->Location = System::Drawing::Point(332, 10);
			this->radioButtonClassSix->Name = L"radioButtonClassSix";
			this->radioButtonClassSix->Size = System::Drawing::Size(59, 17);
			this->radioButtonClassSix->TabIndex = 5;
			this->radioButtonClassSix->TabStop = true;
			this->radioButtonClassSix->Text = L"Class 6";
			this->radioButtonClassSix->UseVisualStyleBackColor = true;
			// 
			// comboBoxClassSize
			// 
			this->comboBoxClassSize->FormattingEnabled = true;
			this->comboBoxClassSize->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"2", L"3", L"4", L"5", L"6" });
			this->comboBoxClassSize->Location = System::Drawing::Point(623, 45);
			this->comboBoxClassSize->Name = L"comboBoxClassSize";
			this->comboBoxClassSize->Size = System::Drawing::Size(189, 21);
			this->comboBoxClassSize->TabIndex = 9;
			this->comboBoxClassSize->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBoxClassSize_SelectedIndexChanged);
			// 
			// radioButtonFnet1
			// 
			this->radioButtonFnet1->AutoSize = true;
			this->radioButtonFnet1->Location = System::Drawing::Point(411, 47);
			this->radioButtonFnet1->Name = L"radioButtonFnet1";
			this->radioButtonFnet1->Size = System::Drawing::Size(85, 17);
			this->radioButtonFnet1->TabIndex = 6;
			this->radioButtonFnet1->TabStop = true;
			this->radioButtonFnet1->Text = L"Fnet-1";
			this->radioButtonFnet1->UseVisualStyleBackColor = true;
			// 
			// radioButtonFnet2
			// 
			this->radioButtonFnet2->AutoSize = true;
			this->radioButtonFnet2->Location = System::Drawing::Point(489, 47);
			this->radioButtonFnet2->Name = L"radioButtonFnet2";
			this->radioButtonFnet2->Size = System::Drawing::Size(85, 17);
			this->radioButtonFnet2->TabIndex = 7;
			this->radioButtonFnet2->TabStop = true;
			this->radioButtonFnet2->Text = L"Fnet-2";
			this->radioButtonFnet2->UseVisualStyleBackColor = true;
			// 
			// checkBoxNormalization
			// 
			this->checkBoxNormalization->AutoSize = true;
			this->checkBoxNormalization->Location = System::Drawing::Point(560, 48);
			this->checkBoxNormalization->Name = L"checkBoxNormalization";
			this->checkBoxNormalization->Size = System::Drawing::Size(60, 17);
			this->checkBoxNormalization->TabIndex = 1;
			this->checkBoxNormalization->Text = L"Norm.";
			this->checkBoxNormalization->UseVisualStyleBackColor = true;
			//
			// buttonResetPoint
			//
			this->buttonResetPoint->Location = System::Drawing::Point(405, 73);
			this->buttonResetPoint->Name = L"buttonResetPoint";
			this->buttonResetPoint->Size = System::Drawing::Size(75, 23);
			this->buttonResetPoint->TabIndex = 3;
			this->buttonResetPoint->Text = L"ResetPoints";
			this->buttonResetPoint->UseVisualStyleBackColor = true;
			this->buttonResetPoint->Click += gcnew System::EventHandler(this, &MyForm::buttonResetPoint_Click);
			// 
			// buttonProcess
			// 
			this->buttonProcess->Location = System::Drawing::Point(485, 73);
			this->buttonProcess->Name = L"buttonProcess";
			this->buttonProcess->Size = System::Drawing::Size(75, 23);
			this->buttonProcess->TabIndex = 3;
			this->buttonProcess->Text = L"Process";
			this->buttonProcess->UseVisualStyleBackColor = true;
			this->buttonProcess->Click += gcnew System::EventHandler(this, &MyForm::buttonProcess_Click);
			// 
			// labelDebug
			// 
			this->labelDebug->AutoSize = true;
			this->labelDebug->Location = System::Drawing::Point(414, 120);
			this->labelDebug->Name = L"labelDebug";
			this->labelDebug->Size = System::Drawing::Size(61, 80);
			this->labelDebug->TabIndex = 5;
			this->labelDebug->Text = L"labelDebug\n";
			// 
			// printDialog1
			// 
			this->printDialog1->UseEXDialog = true;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(824, 379);
			this->Controls->Add(this->comboBoxClassSize);
			this->Controls->Add(this->labelDebug);
			this->Controls->Add(this->buttonProcess);
			this->Controls->Add(this->buttonResetPoint);
			this->Controls->Add(this->groupBoxClass);
			this->Controls->Add(this->radioButtonFnet2);
			this->Controls->Add(this->radioButtonFnet1);
			this->Controls->Add(this->checkBoxNormalization);
			this->Controls->Add(this->pictureBoxCoordinate);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxCoordinate))->EndInit();
			this->groupBoxClass->ResumeLayout(false);
			this->groupBoxClass->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

			refAnnPoints = gcnew AnnPoints();
			classSize = 2;

			firstCall = 1;
			radioButtonFnet1->Checked = true;
			radioButtonClassOne->Checked = true;
		}
#pragma endregion
		private: System::Void buttonProcess_Click(System::Object^  sender, System::EventArgs^  e) {
			AnnPoint* p = refAnnPoints->getPoints();
			int i, j;

			srand(time(NULL));

			double c = LEARNING_RATE_PERCEPTRON;
			if (radioButtonFnet2->Checked){
				c = LEARNING_RATE_DELTA;
			}
			w = gcnew AnnMatrix(classSize, 3);
			double *matrix = w->getMatrix();
			for (i = 0; i < classSize; i++){
				for (j = 0; j < 3; j++){
					matrix[i * 3 + j] = ((double)rand() / RAND_MAX);
				}
			}

			int** dExpect = new int*[classSize];
			
			for (i = 0; i < classSize; i++){
				dExpect[i] = new int[classSize];
			}

			for (i = 0; i < classSize; i++){
				for (j = 0; j < classSize; j++){
					if (i == j){
						dExpect[i][j] = 1;
					}
					else{
						dExpect[i][j] = -1;
					}
				}
			}
			if (checkBoxNormalization->Checked && firstCall){
				firstCall = 0;
				
				int x2sum = 0;
				int y2sum = 0;
				
				double varianceX;
				double varianceY;

				double totalX = 0, totalY = 0;
				int pointNumber;

				AnnPoint* p = refAnnPoints->getPoints();
				while ((p = p->getNext()) != nullptr){
					int x = p->getX();
					int y = p->getY();
							
					totalX += x;
					totalY += y;

					x2sum += (x * x);
					y2sum += (y * y);

					pointNumber++;
				}
				
				totalX /= pointNumber;
				totalY /= pointNumber;

				varianceX = (x2sum / pointNumber) - (totalX * totalX);
				varianceY = (y2sum / pointNumber) - (totalY * totalY);

				// Set points
				p = refAnnPoints->getPoints();
				while ((p = p->getNext()) != nullptr){
					p->setX((p->getX() - totalX) / sqrt(varianceX));
					p->setY((p->getY() - totalY) / sqrt(varianceY));
				}
			}

			int printCounter = 0;
			int finishFlag = 0;
			
			int counter = 0;
			double E = 1;
			while (true){//TODO
				p = p->getNext();
				if (p == nullptr){
					p = refAnnPoints->getPoints();
					counter++;
					if (finishFlag || E < EPSILON){
						break;
					}
					E = 0;
					finishFlag = 1;
					continue;
				}

				AnnMatrix^ y = gcnew AnnMatrix(3, 1);
				double* ptr = y->getMatrix();
				ptr[0] = p->getX();
				ptr[1] = p->getY();
				ptr[2] = BIAS;

				AnnMatrix^ d = w * y;
				double* dFound = d->getMatrix();
				for (i = 0; i < classSize; i++){
					double fTnet;
					double dMinusO = dExpect[i][p->getClassId()] - fNet(radioButtonFnet1->Checked, dFound[i], &fTnet);

					//labelDebug->Text = i + " -> " + E + " " + dMinusO + " " + (fTnet) + "\n";
					//labelDebug->Refresh();
					if (dMinusO > EPSILON || dMinusO < -EPSILON){ // fTnet 0 bakýlmalýmý?
						E += 0.5 * dMinusO * dMinusO;

						AnnMatrix^ wRow = w->getRowVector(i);
						AnnMatrix^ wRowTranspoz = wRow->transpoz();

						wRowTranspoz += (y * (c * dMinusO * fTnet));
						w->updateRow(i, wRowTranspoz);

						finishFlag = 0;

						wRow->~AnnMatrix();
						wRowTranspoz->~AnnMatrix();
					}
				}
				y->~AnnMatrix();
				d->~AnnMatrix();

				if ((printCounter % PRINT_FREQ) == 0){
					pictureBoxCoordinate->Refresh();
				}

				printCounter++;
			}
			pictureBoxCoordinate->Refresh();

			labelDebug->Text = "" + counter + " cycle\nweights:\n";
			for (i = 0; i < classSize; i++){
				labelDebug->Text += "" + w->getMatrix()[i * 3] + " " + w->getMatrix()[i * 3 + 1] + " " + w->getMatrix()[i * 3 + 2] + "\n";
			}
			pictureBoxCoordinate->Refresh();
			w->~AnnMatrix();
			w = nullptr;
		}

		private: System::Void buttonResetPoint_Click(System::Object^  sender, System::EventArgs^  e) {
					 refAnnPoints->~AnnPoints();
					 refAnnPoints = gcnew AnnPoints();
					 
					 labelDebug->Text = "";
					 firstCall = 1;
					 pictureBoxCoordinate->Refresh();
		}

		private: System::Void pictureBoxCoordinate_Click(System::Object^  sender, System::EventArgs^  e) {
					MouseEventArgs ^ms = (MouseEventArgs^)e;
					labelDebug->Text = "";

					if (radioButtonClassOne->Checked){
						labelDebug->Text += "Class 1: ";
						refAnnPoints->addPoint((ms->X - PICTURE_BOX_SIZE_DIV_TWO), (PICTURE_BOX_SIZE_DIV_TWO - ms->Y), 0);
					}
					else if (radioButtonClassTwo->Checked){
						labelDebug->Text += "Class 2: ";
						refAnnPoints->addPoint((ms->X - PICTURE_BOX_SIZE_DIV_TWO), (PICTURE_BOX_SIZE_DIV_TWO - ms->Y), 1);
					}
					else if (radioButtonClassThree->Checked){
						labelDebug->Text += "Class 3: ";
						refAnnPoints->addPoint((ms->X - PICTURE_BOX_SIZE_DIV_TWO), (PICTURE_BOX_SIZE_DIV_TWO - ms->Y), 2);
					}
					else if (radioButtonClassFour->Checked){
						labelDebug->Text += "Class 4: ";
						refAnnPoints->addPoint((ms->X - PICTURE_BOX_SIZE_DIV_TWO), (PICTURE_BOX_SIZE_DIV_TWO - ms->Y), 3);
					}
					else if (radioButtonClassFive->Checked){
						labelDebug->Text += "Class 5: ";
						refAnnPoints->addPoint((ms->X - PICTURE_BOX_SIZE_DIV_TWO), (PICTURE_BOX_SIZE_DIV_TWO - ms->Y), 4);
					}
					else if (radioButtonClassSix->Checked){
						labelDebug->Text += "Class 6: ";
						refAnnPoints->addPoint((ms->X - PICTURE_BOX_SIZE_DIV_TWO), (PICTURE_BOX_SIZE_DIV_TWO - ms->Y), 5);
					}

					labelDebug->Text += "x: " + ms->X + " y: " + ms->Y + " \n";
					labelDebug->Text += "coordinate x: " + (ms->X - PICTURE_BOX_SIZE_DIV_TWO) + " coordinate y: " + (PICTURE_BOX_SIZE_DIV_TWO - ms->Y) + " \n";
					pictureBoxCoordinate->Invalidate();
		}

		private: System::Void MyForm::pictureBoxCoordinate_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e){
				Graphics^ g = e->Graphics;
				Pen^ myPen = gcnew Pen(Color::Black, 2);
				
				g->DrawLine(myPen, PICTURE_BOX_SIZE_DIV_TWO, 0, PICTURE_BOX_SIZE_DIV_TWO, PICTURE_BOX_SIZE);
				g->DrawLine(myPen, 0, PICTURE_BOX_SIZE_DIV_TWO, PICTURE_BOX_SIZE, PICTURE_BOX_SIZE_DIV_TWO);

				int plusSize = 4;

				// ilk nokta geçersiz
				AnnPoint* p = refAnnPoints->getPoints()->getNext();

				while (p != nullptr){
					if (p->getClassId() == 0){
						myPen->Color = Color::Blue;
					}
					else if (p->getClassId() == 1){
						myPen->Color = Color::Red;
					}
					else if (p->getClassId() == 2){
						myPen->Color = Color::Yellow;
					}
					else if (p->getClassId() == 3){
						myPen->Color = Color::Green;
					}
					else if (p->getClassId() == 4){
						myPen->Color = Color::Purple;
					}
					else if (p->getClassId() == 5){
						myPen->Color = Color::Cyan;
					}

					int x, y;
					if (checkBoxNormalization->Checked){
						x = PICTURE_BOX_SIZE_DIV_TWO + p->getX() * ZOOM;
						y = PICTURE_BOX_SIZE_DIV_TWO - p->getY() * ZOOM;
					}
					else {
						x = PICTURE_BOX_SIZE_DIV_TWO + p->getX();
						y = PICTURE_BOX_SIZE_DIV_TWO - p->getY();
					}
					
					g->DrawLine(myPen, x - plusSize, y, x + plusSize, y);
					g->DrawLine(myPen, x, y - plusSize, x, y + plusSize);
					p = p->getNext();

					if (w != nullptr){
						double* ptr = w->getMatrix();

						int pad = 1;
						if (checkBoxNormalization->Checked){
							pad = ZOOM;
						}
						for (int i = 0; i < classSize; i++){
							if (ptr[i * 3 + 1] == 0){
								ptr[i * 3 + 1] = 0.00001;
							}
							
							int px1 = 0;
							int py1 = ((px1 - PICTURE_BOX_SIZE_DIV_TWO) * ptr[i * 3] + PICTURE_BOX_SIZE_DIV_TWO * ptr[i * 3 + 1] + ptr[i * 3 + 2] * pad) / (ptr[i * 3 + 1]);

							int px2 = PICTURE_BOX_SIZE;
							int py2 = ((px2 - PICTURE_BOX_SIZE_DIV_TWO) * ptr[i * 3] + PICTURE_BOX_SIZE_DIV_TWO * ptr[i * 3 + 1] + ptr[i * 3 + 2] * pad) / (ptr[i * 3 + 1]);
							
							if (i == 0){
								myPen->Color = Color::Blue;
							}
							else if (i == 1){
								myPen->Color = Color::Red;
							}
							else if (i == 2){
								myPen->Color = Color::Yellow;
							}
							else if (i == 3){
								myPen->Color = Color::Green;
							}
							else if (i == 4){
								myPen->Color = Color::Purple;
							}
							else if (i == 5){
								myPen->Color = Color::Cyan;
							}
							g->DrawLine(myPen, px1, py1, px2, py2);
						}
					}
				}
		}
		
		private: double fNet(System::Boolean simpleAlg, double net, double *fTnet){
			if (simpleAlg){
				*fTnet = 1;
				return (net >= 0 ? 1 : -1);
			}
			else{
				double temp = exp(-net) + 1;
				if (temp == 0){
					temp = 0.0000001;
				}
				double fNet = (2.0 / (temp) - 1.0);
				
				*fTnet = 0.5 * (1 - (fNet * fNet));
				return fNet;
			}
		}

		private: System::Void comboBoxClassSize_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
					 classSize = comboBoxClassSize->SelectedIndex + 2;
					 labelDebug->Text += "" + classSize;
		}
};
}
