TButton *guiButton[18];
TCheckBox *guiCheckBox[15];
TLabel *guiLabel[32];
TGroupBox *guiGroupBox[17];
TForm *guiForm[3];
TMenuItem *guiMenuItem[20];
TTabSheet *guiTabSheet[9];
TRadioButton *guiRadioButton[4];


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