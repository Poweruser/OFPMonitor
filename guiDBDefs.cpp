TButton *guiButton[13];
TCheckBox *guiCheckBox[12];
TLabel *guiLabel[17];
TGroupBox *guiGroupBox[9];
TForm *guiForm[2];
TMenuItem *guiMenuItem[20];
TTabSheet *guiTabSheet[7];


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