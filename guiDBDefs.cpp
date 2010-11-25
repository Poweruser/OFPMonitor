TButton *guiButton[12];
TCheckBox *guiCheckBox[10];
TLabel *guiLabel[17];
TGroupBox *guiGroupBox[7];
TForm *guiForm[3];
TMenuItem *guiMenuItem[12];
TStatusPanel *guiStatusPanel[10];

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