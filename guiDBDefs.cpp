TButton *guiButton[19];
TCheckBox *guiCheckBox[23];
TLabel *guiLabel[31];
TGroupBox *guiGroupBox[15];
TForm *guiForm[3];
TMenuItem *guiMenuItem[17];
TTabSheet *guiTabSheet[9];
TRadioButton *guiRadioButton[2];


/**
   Object that stores an identifier and the 
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