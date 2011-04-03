TButton *guiButton[12];
TCheckBox *guiCheckBox[10];
TLabel *guiLabel[18];
TGroupBox *guiGroupBox[8];
TForm *guiForm[3];
TMenuItem *guiMenuItem[19];
TStatusPanel *guiStatusPanel[10];
TTabSheet *guiTabSheet[2];


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