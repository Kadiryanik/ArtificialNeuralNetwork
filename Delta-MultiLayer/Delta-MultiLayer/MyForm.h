#pragma once
#include "AnnPoints.h"
#include "AnnMatrix.h"

#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

#define PICTURE_BOX_SIZE 351
#define PICTURE_BOX_SIZE_DIV_TWO 175

#define DEBUG 0
#define PRINT_ERROR 0
#define PRINT_FREQ 1000

#define ZOOM 50

#define BIAS 1
#define EPSILON 0.001

#define LEARNING_RATE_PERCEPTRON 0.2
#define LEARNING_RATE_DELTA 0.7

namespace DeltaMultilayer {
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
	private: System::Windows::Forms::ComboBox^  comboBoxHiddenLayer;
	private: System::Windows::Forms::RadioButton^  radioButtonFnet1;
	private: System::Windows::Forms::CheckBox^  checkBoxNormalization;
	private: System::Windows::Forms::Button^  buttonResetPoint;
	private: System::Windows::Forms::Button^  buttonProcess;
	private: System::Windows::Forms::Button^  buttonDeleteLastPoint;
	private: System::Windows::Forms::Button^  buttonStorePointReset;
	private: System::Windows::Forms::Label^  labelInfo;
	private: System::Windows::Forms::Label^  labelDebug;
#if DEBUG
	private: System::Windows::Forms::Label^  labelDebugTwo;
#endif
	private: System::Windows::Forms::Label^  labelCycleError;
	private: System::Windows::Forms::PrintDialog^  printDialog1;


	protected:

	protected:

	private:
		AnnPoints^ refAnnPoints;
		AnnPoints^ refAnnNormilizedPoints;
		AnnMatrix^ W;
		AnnMatrix^ V;

		int counterHolder;
		double totalX, totalY;
		double standartDevX, standartDevY;

		int classSize;
		int hiddenLayerSize;
		int firstCall;
		int isDone;
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
			this->comboBoxHiddenLayer = (gcnew System::Windows::Forms::ComboBox());
			this->radioButtonFnet1 = (gcnew System::Windows::Forms::RadioButton());
			this->checkBoxNormalization = (gcnew System::Windows::Forms::CheckBox());
			this->buttonResetPoint = (gcnew System::Windows::Forms::Button());
			this->buttonProcess = (gcnew System::Windows::Forms::Button());
			this->buttonDeleteLastPoint = (gcnew System::Windows::Forms::Button());
			this->buttonStorePointReset = (gcnew System::Windows::Forms::Button());
			this->labelInfo = (gcnew System::Windows::Forms::Label());
			this->labelDebug = (gcnew System::Windows::Forms::Label());
#if DEBUG
			this->labelDebugTwo = (gcnew System::Windows::Forms::Label());
#endif
			this->labelCycleError = (gcnew System::Windows::Forms::Label());
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
			this->radioButtonClassOne->ForeColor = Color::Blue;
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
			this->radioButtonClassTwo->ForeColor = Color::Red;
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
			this->radioButtonClassThree->ForeColor = Color::Orange;
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
			this->radioButtonClassFour->ForeColor = Color::Green;
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
			this->radioButtonClassFive->ForeColor = Color::Purple;
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
			this->radioButtonClassSix->ForeColor = Color::Cyan;
			// 
			// comboBoxClassSize
			// 
			this->comboBoxClassSize->FormattingEnabled = true;
			this->comboBoxClassSize->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"2", L"3", L"4", L"5", L"6" });
			this->comboBoxClassSize->Location = System::Drawing::Point(703, 60);
			this->comboBoxClassSize->Name = L"comboBoxClassSize";
			this->comboBoxClassSize->Size = System::Drawing::Size(80, 21);
			this->comboBoxClassSize->TabIndex = 9;
			this->comboBoxClassSize->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBoxClassSize_SelectedIndexChanged);
			// 
			// comboBoxHiddenLayer
			// 
			this->comboBoxHiddenLayer->FormattingEnabled = true;
			this->comboBoxHiddenLayer->Items->AddRange(gcnew cli::array< System::Object^  >(10) { L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", L"10", L"11" });
			this->comboBoxHiddenLayer->Location = System::Drawing::Point(593, 60);
			this->comboBoxHiddenLayer->Name = L"comboBoxHiddenLayer";
			this->comboBoxHiddenLayer->Size = System::Drawing::Size(80, 21);
			this->comboBoxHiddenLayer->TabIndex = 9;
			this->comboBoxHiddenLayer->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBoxHiddenLayer_SelectedIndexChanged);
			// 
			// radioButtonFnet1
			// 
			this->radioButtonFnet1->AutoSize = true;
			this->radioButtonFnet1->Location = System::Drawing::Point(411, 47);
			this->radioButtonFnet1->Name = L"radioButtonFnet1";
			this->radioButtonFnet1->Size = System::Drawing::Size(85, 17);
			this->radioButtonFnet1->TabIndex = 6;
			this->radioButtonFnet1->TabStop = true;
			this->radioButtonFnet1->Text = L"Delta";
			this->radioButtonFnet1->UseVisualStyleBackColor = true;
			// 
			// checkBoxNormalization
			// 
			this->checkBoxNormalization->AutoSize = true;
			this->checkBoxNormalization->Location = System::Drawing::Point(480, 48);
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
			// buttonDeleteLastPoint
			// 
			this->buttonDeleteLastPoint->Location = System::Drawing::Point(570, 100);
			this->buttonDeleteLastPoint->Name = L"buttonDeleteLastPoint";
			this->buttonDeleteLastPoint->Size = System::Drawing::Size(100, 23);
			this->buttonDeleteLastPoint->TabIndex = 3;
			this->buttonDeleteLastPoint->Text = L"DeleteLastPoint";
			this->buttonDeleteLastPoint->UseVisualStyleBackColor = true;
			this->buttonDeleteLastPoint->Click += gcnew System::EventHandler(this, &MyForm::buttonDeleteLastPoint_Click);
			// 
			// buttonStorePointReset
			// 
			this->buttonStorePointReset->Location = System::Drawing::Point(405, 100);
			this->buttonStorePointReset->Name = L"buttonStorePointReset";
			this->buttonStorePointReset->Size = System::Drawing::Size(155, 23);
			this->buttonStorePointReset->TabIndex = 3;
			this->buttonStorePointReset->Text = L"StorePoint-Reset";
			this->buttonStorePointReset->UseVisualStyleBackColor = true;
			this->buttonStorePointReset->Click += gcnew System::EventHandler(this, &MyForm::buttonStorePointReset_Click);
			// 
			// labelInfo
			// 
			this->labelInfo->AutoSize = true;
			this->labelInfo->Location = System::Drawing::Point(593, 45);
			this->labelInfo->Name = L"labelInfo";
			this->labelInfo->Size = System::Drawing::Size(200, 40);
			this->labelInfo->TabIndex = 5;
			this->labelInfo->Text = L"HiddenLayer                 ClassSize\n";
			this->labelInfo->ForeColor = Color::Black;
			// 
			// labelDebug
			// 
			this->labelDebug->AutoSize = true;
			this->labelDebug->Location = System::Drawing::Point(414, 170);
			this->labelDebug->Name = L"labelDebug";
			this->labelDebug->Size = System::Drawing::Size(60, 50);
			this->labelDebug->TabIndex = 5;
			this->labelDebug->Text = L"labelDebug\n";
			this->labelDebug->ForeColor = Color::Blue;
#if DEBUG
			// 
			// labelDebugTwo
			// 
			this->labelDebugTwo->AutoSize = true;
			this->labelDebugTwo->Location = System::Drawing::Point(600, 170);
			this->labelDebugTwo->Name = L"labelDebugTwo";
			this->labelDebugTwo->Size = System::Drawing::Size(60, 50);
			this->labelDebugTwo->TabIndex = 5;
			this->labelDebugTwo->Text = L"labelDebugTwo\n";
			this->labelDebugTwo->ForeColor = Color::Blue;
#endif
			// 
			// labelCycleError
			// 
			this->labelCycleError->AutoSize = true;
			this->labelCycleError->Location = System::Drawing::Point(414, 140);
			this->labelCycleError->Name = L"labelCycleError";
			this->labelCycleError->Size = System::Drawing::Size(61, 30);
			this->labelCycleError->TabIndex = 5;
			this->labelCycleError->Text = L"labelCycleError\n";
			this->labelCycleError->ForeColor = Color::DarkRed;
			// 
			// printDialog1
			// 
			this->printDialog1->UseEXDialog = true;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			//this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->BackColor = Color::Gray;
			this->ClientSize = System::Drawing::Size(824, 379);
			this->Controls->Add(this->comboBoxClassSize);
			this->Controls->Add(this->comboBoxHiddenLayer);
			this->Controls->Add(this->labelInfo);
			this->Controls->Add(this->labelDebug);
#if DEBUG
			this->Controls->Add(this->labelDebugTwo);
#endif
			this->Controls->Add(this->labelCycleError);
			this->Controls->Add(this->buttonStorePointReset);
			this->Controls->Add(this->buttonProcess);
			this->Controls->Add(this->buttonDeleteLastPoint);
			this->Controls->Add(this->buttonResetPoint);
			this->Controls->Add(this->groupBoxClass);
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
			refAnnNormilizedPoints = nullptr;
			classSize = 2;
			hiddenLayerSize = 4;

			labelDebug->Text = "classSize: 2\nhiddenLayer: 4\n";

			counterHolder = 0;
			isDone = 0;
			firstCall = 1;
			radioButtonFnet1->Checked = true;
			radioButtonClassOne->Checked = true;
		}
#pragma endregion
		private: System::Void buttonProcess_Click(System::Object^  sender, System::EventArgs^  e) {
			int i, j;
			double c = LEARNING_RATE_DELTA;

			checkBoxNormalization->Checked = true;
			isDone = 0;

			int I = 2; // input size (x, y)
			int K = classSize;
			int J = hiddenLayerSize;

			if (firstCall){
				srand(time(NULL));

				V = gcnew AnnMatrix(J, I + 1);
				W = gcnew AnnMatrix(K, J + 1);

				//TODO: V baslangicta 1 olabilir?
				double *matrix = V->getMatrix();
				for (i = 0; i < V->getRow(); i++){
					for (j = 0; j < V->getColumn(); j++){
						matrix[i * V->getColumn() + j] = ((double)rand() / RAND_MAX);
					}
				}

				matrix = W->getMatrix();
				for(i = 0; i < W->getRow(); i++){
					for (j = 0; j < W->getColumn(); j++){
						matrix[i * W->getColumn() + j] = ((double)rand() / RAND_MAX);
					}
				}

				firstCall = 0;
			}

			if (checkBoxNormalization->Checked){
				if (refAnnNormilizedPoints != nullptr){
					// TODO: deconstructer duzenlenicek
					delete refAnnNormilizedPoints;
				}
				refAnnNormilizedPoints = gcnew AnnPoints();

				double x2sum = 0;
				double y2sum = 0;
				
				double varianceX;
				double varianceY;

				totalX = 0;
				totalY = 0;
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

				standartDevX = sqrt(varianceX);
				standartDevY = sqrt(varianceY);

				// Set points
				p = refAnnPoints->getPoints();
				while ((p = p->getNext()) != nullptr){
					refAnnNormilizedPoints->addPoint((p->getX() - totalX) / standartDevX,
													 (p->getY() - totalY) / standartDevY,
													 p->getClassId());
				}
			}
			// paint normilized dataset
			pictureBoxCoordinate->Refresh();

			AnnPoint* p = refAnnNormilizedPoints->getPoints();
			int counter = 0;

			double E = 1;
			clock_t start = clock();
			while (true){
				p = p->getNext();
				if (p == nullptr){
					p = refAnnNormilizedPoints->getPoints();
					
					if (E < EPSILON || counter > 50000){
						break;
					}
					counter++;
#if PRINT_ERROR
					labelCycleError->Text = "" + counter + ". cycle E: " + E + "\n";
					labelCycleError->Refresh();
#else
					if ((counter % PRINT_FREQ) == 0){
						labelCycleError->Text = "" + counter + ". cycle E: " + E + "\n";
						labelCycleError->Refresh();
					}
#endif				
					E = 0;
					continue;
				}

				AnnMatrix^ z = gcnew AnnMatrix(I + 1, 1);
				z->matrix[0] = p->getX();
				z->matrix[1] = p->getY();
				z->matrix[2] = BIAS;

				// Jx1
				AnnMatrix^ temp_y = (V * z)->fnet(1); // J x 1
				
				// y ye bias ekle J+1 x 1
				AnnMatrix^ y = gcnew AnnMatrix(temp_y->getRow() + 1, temp_y->getColumn());
				
				for (int i = 0; i < temp_y->getRow(); i++){
					y->matrix[i] = temp_y->matrix[i];
				}
				y->matrix[temp_y->getRow()] = BIAS;

				// W: K x (J+1) y: J+1 x 1
				AnnMatrix^ o = (W * y)->fnet(1); // K x 1
				AnnMatrix^ d = gcnew AnnMatrix(K, 1);
				
				for (int i = 0; i < K; i++){
					if (p->getClassId() == i){
						d->matrix[i] = 1;
					}
					else{
						d->matrix[i] = -1;
					}
				}
				// K x 1
				AnnMatrix^ dMinusO = d - o;
				
				for (int i = 0; i < K; i++){
					E += 0.5 * (dMinusO->matrix[i] * dMinusO->matrix[i]);
				}
				// K x 1
				AnnMatrix^ fTnetK = gcnew AnnMatrix(K, 1);
				for (int i = 0; i < K; i++){
					fTnetK->matrix[i] = 0.5 * (1 - (o->matrix[i] * o->matrix[i]));
				}

				// K x 1
				AnnMatrix^ delta_o = dMinusO * fTnetK;

				double _m = 1; //mü

				// K x 1 .. 1 x J+1
				AnnMatrix^ yTranspoz = y->transpoz();
				
				// W update
				AnnMatrix^ product_temp = (delta_o * yTranspoz);
				W += (product_temp * _m);
				delete product_temp;
#if DEBUG
				labelDebugTwo->Text = "";
				for (int i = 0; i < W->getRow(); i++){
					for (int j = 0; j < W->getColumn(); j++){
						labelDebugTwo->Text += " W[" + i + "][" + j + "]: " + W->matrix[i * W->getColumn() + j] + "\n";
					}
				}
				labelDebugTwo->Refresh();
#endif

				delete yTranspoz;

				// J x 1
				AnnMatrix^ fTnetJ = gcnew AnnMatrix(J, 1);

				for (int i = 0; i < J; i++){
					fTnetJ->matrix[i] = 0.5 * (1 - (temp_y->matrix[i] * temp_y->matrix[i]));
				}

				// J x 1
				AnnMatrix^ delta_y = gcnew AnnMatrix(J, 1);

				for (int j = 0; j < J; j++){
					double sum = 0;
					for (int k = 0; k < K; k++){
						sum += delta_o->matrix[k] * W->matrix[k * W->getColumn() + j];
					}
					delta_y->matrix[j] = fTnetJ->matrix[j] * sum;
				}

				AnnMatrix^ zTranspoz = z->transpoz();

				// V update
				product_temp = (delta_y * zTranspoz);
				V += (product_temp * _m);
				delete product_temp;
#if DEBUG
				labelDebug->Text = "";
				for (int i = 0; i < V->getRow(); i++){
					for (int j = 0; j < V->getColumn(); j++){
						labelDebug->Text += " V[" + i + "][" + j + "]: " + V->matrix[i * V->getColumn() + j] + "\n";
					}
				}
				labelDebug->Refresh();
#endif
				delete zTranspoz;
				delete z;
				delete temp_y;
				delete y;
				delete o;
				delete d;
				delete dMinusO;
				delete delta_o;
				delete delta_y;
				delete fTnetJ;
				delete fTnetK;
			}
			clock_t end = clock();
			isDone = 1;
			
			counterHolder += counter;
			labelCycleError->Text = "" + counterHolder + "(" + counter + ") cycle. " + ((double)(end - start) / (CLOCKS_PER_SEC))+ " sec. E: " + E + "\n";
			labelCycleError->Refresh();
			pictureBoxCoordinate->Refresh();
		}

		private: System::Void buttonResetPoint_Click(System::Object^  sender, System::EventArgs^  e) {
					 delete refAnnPoints;
					 delete refAnnNormilizedPoints;
					 refAnnPoints = gcnew AnnPoints();
					 refAnnNormilizedPoints = gcnew AnnPoints();
					 
					 labelDebug->Text = "";

					 checkBoxNormalization->Checked = false;
					 counterHolder = 0;
					 isDone = 0;
					 firstCall = 1;
					 pictureBoxCoordinate->Refresh();
		}

		private: System::Void buttonStorePointReset_Click(System::Object^  sender, System::EventArgs^  e) {
					 labelDebug->Text = "";

					 checkBoxNormalization->Checked = false;
					 counterHolder = 0;
					 isDone = 0;
					 firstCall = 1;
					 pictureBoxCoordinate->Refresh();
		}

		private: System::Void buttonDeleteLastPoint_Click(System::Object^  sender, System::EventArgs^  e) {
					 if (refAnnPoints != nullptr){
						AnnPoint* p = refAnnPoints->getPoints();
						if (p->getNext() == nullptr){ //empty
							return;
						}
						while (p->getNext()->getNext() != nullptr){
							p = p->getNext();
						}
						delete p->getNext();
						p->setNext(nullptr);
					 }
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

				if (isDone){
					for (int i = -PICTURE_BOX_SIZE_DIV_TWO; i < PICTURE_BOX_SIZE_DIV_TWO; i += 3){
						for (int j = PICTURE_BOX_SIZE_DIV_TWO; j > -PICTURE_BOX_SIZE_DIV_TWO; j -= 3){
							AnnMatrix^ x = gcnew AnnMatrix(3, 1);
							x->matrix[0] = (i - totalX) / standartDevX;
							x->matrix[1] = (j - totalY) / standartDevY;
							x->matrix[2] = BIAS;

							AnnMatrix^ temp_y = (V * x)->fnet(1);
							AnnMatrix^ y = gcnew AnnMatrix(temp_y->getRow() + 1, temp_y->getColumn());

							for (int i = 0; i < temp_y->getRow(); i++){
								y->matrix[i] = temp_y->matrix[i];
							}
							y->matrix[temp_y->getRow()] = BIAS;

							AnnMatrix^ o = (W * y)->fnet(1);

							int classId = o->maxSelector();
							if (classId == 0){
								myPen->Color = Color::Blue;
							}
							else if (classId == 1){
								myPen->Color = Color::Red;
							}
							else if (classId == 2){
								myPen->Color = Color::Orange;
							}
							else if (classId == 3){
								myPen->Color = Color::Green;
							}
							else if (classId == 4){
								myPen->Color = Color::Purple;
							}
							else if (classId == 5){
								myPen->Color = Color::Cyan;
							}
							else{
								myPen->Color = Color::Black;
							}
							int coor_x = i + 175;
							int coor_y = 175 - j;

							g->DrawLine(myPen, coor_x, coor_y, coor_x + 1, coor_y);

							delete x;
							delete temp_y;
							delete y;
							delete o;
						}
					}

					while (p != nullptr){
						if (p->getClassId() == 0){
							myPen->Color = Color::Blue;
						}
						else if (p->getClassId() == 1){
							myPen->Color = Color::Red;
						}
						else if (p->getClassId() == 2){
							myPen->Color = Color::Orange;
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
						x = PICTURE_BOX_SIZE_DIV_TWO + p->getX();
						y = PICTURE_BOX_SIZE_DIV_TWO - p->getY();
						
						g->DrawLine(myPen, x - plusSize, y, x + plusSize, y);
						g->DrawLine(myPen, x, y - plusSize, x, y + plusSize);
						p = p->getNext();
					}
				}
				else{
					if (checkBoxNormalization->Checked){
						p = refAnnNormilizedPoints->getPoints()->getNext();
					}
					while (p != nullptr){
						if (p->getClassId() == 0){
							myPen->Color = Color::Blue;
						}
						else if (p->getClassId() == 1){
							myPen->Color = Color::Red;
						}
						else if (p->getClassId() == 2){
							myPen->Color = Color::Orange;
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
					}
				}
		}

		private: System::Void comboBoxClassSize_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
					 classSize = comboBoxClassSize->SelectedIndex + 2;
					 labelDebug->Text += "classSize: " + classSize + "\n";
		}
		private: System::Void comboBoxHiddenLayer_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
					 hiddenLayerSize = comboBoxHiddenLayer->SelectedIndex + 2;
					 labelDebug->Text += "hiddenLayer: " + hiddenLayerSize + "\n";
		}
};
}
