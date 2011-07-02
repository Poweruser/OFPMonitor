TButton *guiButton[14];
TCheckBox *guiCheckBox[13];
TLabel *guiLabel[21];
TGroupBox *guiGroupBox[11];
TForm *guiForm[2];
TMenuItem *guiMenuItem[19];
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