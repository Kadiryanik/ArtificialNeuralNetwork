#pragma once
#include "AnnPoints.h"
#include "AnnMatrix.h"

#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

#define CLASS_ONE_D (-1)
#define CLASS_TWO_D (1)
#define PICTURE_BOX_SIZE 351
#define PICTURE_BOX_SIZE_DIV_TWO 175

namespace ysa {
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
	private: System::Windows::Forms::RadioButton^  radioButtonFnet1;
	private: System::Windows::Forms::RadioButton^  radioButtonFnet2;
	private: System::Windows::Forms::Button^  buttonResetPoint;
	private: System::Windows::Forms::Button^  buttonProcess;
	private: System::Windows::Forms::Label^  labelDebug;
	private: System::Windows::Forms::PrintDialog^  printDialog1;

	protected:

	private:
		AnnPoints^ refAnnPoints;
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
			this->radioButtonFnet1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonFnet2 = (gcnew System::Windows::Forms::RadioButton());
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
			this->groupBoxClass->Controls->Add(this->radioButtonClassTwo);
			this->groupBoxClass->Controls->Add(this->radioButtonClassOne);
			this->groupBoxClass->Location = System::Drawing::Point(404, 6);
			this->groupBoxClass->Name = L"groupBoxClass";
			this->groupBoxClass->Size = System::Drawing::Size(156, 33);
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
			this->radioButtonClassTwo->Location = System::Drawing::Point(85, 10);
			this->radioButtonClassTwo->Name = L"radioButtonClassTwo";
			this->radioButtonClassTwo->Size = System::Drawing::Size(59, 17);
			this->radioButtonClassTwo->TabIndex = 1;
			this->radioButtonClassTwo->TabStop = true;
			this->radioButtonClassTwo->Text = L"Class 2";
			this->radioButtonClassTwo->UseVisualStyleBackColor = true;
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
			this->Controls->Add(this->labelDebug);
			this->Controls->Add(this->buttonProcess);
			this->Controls->Add(this->buttonResetPoint);
			this->Controls->Add(this->groupBoxClass);
			this->Controls->Add(this->radioButtonFnet2);
			this->Controls->Add(this->radioButtonFnet1);
			this->Controls->Add(this->pictureBoxCoordinate);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxCoordinate))->EndInit();
			this->groupBoxClass->ResumeLayout(false);
			this->groupBoxClass->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

			refAnnPoints = gcnew AnnPoints();
			radioButtonFnet1->Checked = true;
		}
#pragma endregion
		private: System::Void buttonProcess_Click(System::Object^  sender, System::EventArgs^  e) {
			AnnPoint* p = refAnnPoints->getPoints();
			int classOneSize = 0;
			int classTwoSize = 0;

			while ((p = p->getNext()) != nullptr){
				if (p->getClassId() == CLASS_ONE_D){
					classOneSize++;
				}
				else if (p->getClassId() == CLASS_TWO_D){
					classTwoSize++;
				}
			}

			AnnMatrix^ x1 = gcnew AnnMatrix(3, classOneSize);
			AnnMatrix^ x2 = gcnew AnnMatrix(3, classTwoSize);

			p = refAnnPoints->getPoints();

			double *classOnePtr = x1->getMatrix();
			double *classTwoPtr = x2->getMatrix();

			int i = 0, j = 0;

			while ((p = p->getNext()) != nullptr){
				int k = 0;
				if (p->getClassId() == CLASS_ONE_D){
					classOnePtr[i + k * classOneSize] = p->getX();
					k++;
					classOnePtr[i + k * classOneSize] = p->getY();
					k++;
					classOnePtr[i + k * classOneSize] = 1;
					i++;
				}
				else if (p->getClassId() == CLASS_TWO_D){
					classTwoPtr[j + k * classTwoSize] = p->getX();
					k++;
					classTwoPtr[j + k * classTwoSize] = p->getY();
					k++;
					classTwoPtr[j + k * classTwoSize] = 1;
					j++;
				}
			}

			double c = 0.2;
			AnnMatrix^ w = gcnew AnnMatrix(3, 1);
			w->getMatrix()[0] = 0.5;
			w->getMatrix()[1] = 1;
			w->getMatrix()[2] = -1;
			
			int isDone = 0;
			int counter = 0;
			while (!isDone){
				isDone = 1;

				if (classOneSize >= classTwoSize){
					int j = 0;
					for (i = 0; i < classOneSize; i++){
						AnnMatrix^ columnVector = x1->getColumnVector(i);
						AnnMatrix^ wTranspoz = w->transpoz();
						AnnMatrix^ netMatrix = (wTranspoz * columnVector);

						double net = netMatrix->getMatrix()[0];
						double fTnet;
						double dMinusO = fNet(radioButtonFnet1->Checked, CLASS_ONE_D, net, &fTnet);
						if (dMinusO != 0 && fTnet != 0){
							w += (columnVector * (c * dMinusO * fTnet));
							isDone = 0;
						}
						columnVector->~AnnMatrix();
						wTranspoz->~AnnMatrix();
						netMatrix->~AnnMatrix();

						if (j < classTwoSize){
							columnVector = x2->getColumnVector(j);
							wTranspoz = w->transpoz();
							netMatrix = (wTranspoz * columnVector);

							double net = netMatrix->getMatrix()[0];
							double fTnet;
							double dMinusO = fNet(radioButtonFnet1->Checked, CLASS_TWO_D, net, &fTnet);
							if (dMinusO != 0 && fTnet != 0){
								w += (columnVector * (c * dMinusO * fTnet));
								isDone = 0;
							}
							j++;
							columnVector->~AnnMatrix();
							wTranspoz->~AnnMatrix();
							netMatrix->~AnnMatrix();
						}
					}
				}
				else{
					int j = 0;
					for (i = 0; i < classTwoSize; i++){
						AnnMatrix^ columnVector = x2->getColumnVector(i);
						AnnMatrix^ wTranspoz = w->transpoz();
						AnnMatrix^ netMatrix = (wTranspoz * columnVector);

						double net = netMatrix->getMatrix()[0];
						double fTnet;
						double dMinusO = fNet(radioButtonFnet1->Checked, CLASS_TWO_D, net, &fTnet);
						if (dMinusO != 0 && fTnet != 0){
							w += (columnVector * (c * dMinusO * fTnet));
							isDone = 0;
						}
						j++;
						columnVector->~AnnMatrix();
						wTranspoz->~AnnMatrix();
						netMatrix->~AnnMatrix();
						if (j < classOneSize){
							columnVector = x1->getColumnVector(j);
							wTranspoz = w->transpoz();
							netMatrix = (wTranspoz * columnVector);

							double net = netMatrix->getMatrix()[0];
							double fTnet;
							double dMinusO = fNet(radioButtonFnet1->Checked, CLASS_ONE_D, net, &fTnet);
							if (dMinusO != 0 && fTnet != 0){
								w += (columnVector * (c * dMinusO * fTnet));
								isDone = 0;
							}
							columnVector->~AnnMatrix();
							wTranspoz->~AnnMatrix();
							netMatrix->~AnnMatrix();
						}
					}
				}

				counter++;

				if ((counter % 100) == 0 || isDone){
					double* matrixHolder = w->getMatrix();

					if (matrixHolder[1] == 0){
						matrixHolder[1] = 0.00001;
					}

					int px1 = 0;
					int py1 = ((px1 - PICTURE_BOX_SIZE_DIV_TWO) * matrixHolder[0] 
								+ PICTURE_BOX_SIZE_DIV_TWO * matrixHolder[1] + matrixHolder[2]) / (matrixHolder[1]);
					refAnnPoints->addPoint(px1, py1, 0);

					int px2 = PICTURE_BOX_SIZE;
					int py2 = ((px2 - PICTURE_BOX_SIZE_DIV_TWO) * matrixHolder[0] + PICTURE_BOX_SIZE_DIV_TWO * matrixHolder[1] + matrixHolder[2]) / (matrixHolder[1]);
					refAnnPoints->addPoint(px2, py2, 0);

					pictureBoxCoordinate->Refresh();
				}
			}
			labelDebug->Text = "Result w:\n    " + w->getMatrix()[0] + "\n    " + w->getMatrix()[1] + "\n    " + w->getMatrix()[2] + " \nCounter: " + counter + "\n";
			pictureBoxCoordinate->Refresh();
		}

		private: System::Void buttonResetPoint_Click(System::Object^  sender, System::EventArgs^  e) {
			refAnnPoints->~AnnPoints();
			refAnnPoints = gcnew AnnPoints();

			labelDebug->Text = "";
			pictureBoxCoordinate->Refresh();
		}

		private: System::Void pictureBoxCoordinate_Click(System::Object^  sender, System::EventArgs^  e) {
			MouseEventArgs ^ms = (MouseEventArgs^)e;
			labelDebug->Text = "";

			if (radioButtonClassOne->Checked){
				labelDebug->Text += "Class 1: ";
				refAnnPoints->addPoint((ms->X - PICTURE_BOX_SIZE_DIV_TWO), (PICTURE_BOX_SIZE_DIV_TWO - ms->Y), CLASS_ONE_D);
			}
			else if (radioButtonClassTwo->Checked){
				labelDebug->Text += "Class 2: ";
				refAnnPoints->addPoint((ms->X - PICTURE_BOX_SIZE_DIV_TWO), (PICTURE_BOX_SIZE_DIV_TWO - ms->Y), CLASS_TWO_D);
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

			int plusSize = 5;
			// ilk nokta geçersiz
			AnnPoint* p = refAnnPoints->getPoints()->getNext();

			while (p != nullptr){
				if (p->getClassId() == 0){
					//TODO: draw line 
					while (p->getNext()->getNext() != nullptr){
						p = p->getNext();
					}
					myPen->Color = Color::Purple;

					int x = p->getX();
					int y = p->getY();
					
					int endX = p->getNext()->getX();
					int endY = p->getNext()->getY();

					g->DrawLine(myPen, x, y, endX, endY);
					break;
				}
				else if (p->getClassId() == CLASS_ONE_D){
					myPen->Color = Color::Blue;
				}
				else if(p->getClassId() == CLASS_TWO_D){
					myPen->Color = Color::Red;
				}

				int x = PICTURE_BOX_SIZE_DIV_TWO + p->getX();
				int y = PICTURE_BOX_SIZE_DIV_TWO - p->getY();
				g->DrawLine(myPen, x - plusSize, y, x + plusSize, y);
				g->DrawLine(myPen, x, y - plusSize, x, y + plusSize);
				p = p->getNext();
			}
		}
		
		private: double fNet(System::Boolean simpleAlg, int d, double net, double *fTnet){
			if (simpleAlg){
				*fTnet = 1;
				return (d - (net >= 0 ? 1 : -1));
			}
			else{
				double temp = exp(net) + 1;
				if (temp == 0){
					temp = 0.0000001;
				}
				double fNet = (2.0 / (temp)) - 1.0;
				if (fNet < 0.5 && fNet > -0.5){
					*fTnet = 0.5;
					return 0;
				}
				else{
					*fTnet = 0.5 * (1 - (fNet * fNet));
					return fNet;
				}
			}
		}
};
}
