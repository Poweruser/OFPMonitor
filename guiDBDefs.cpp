TButton *guiButton[18];
TCheckBox *guiCheckBox[23];
TLabel *guiLabel[31];
TGroupBox *guiGroupBox[16];
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