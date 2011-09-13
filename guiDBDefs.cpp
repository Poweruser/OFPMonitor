TButton *guiButton[17];
TCheckBox *guiCheckBox[15];
TLabel *guiLabel[27];
TGroupBox *guiGroupBox[14];
TForm *guiForm[3];
TMenuItem *guiMenuItem[20];
TTabSheet *guiTabSheet[8];
TRadioButton *guiRadioButton[2];


/**
   Object that stores and identifier and the 
   corresponding String of a language
 */

class guiString {
	public:
		String identifier;
		String value;
		guiString(String i, String v) {
			this->identifier = i;
			this->value = v;
		}
};

list<guiString> guiStrings;