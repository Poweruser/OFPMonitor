#include "FileVersion.h"

FileVersion::FileVersion(String file) {
	unsigned long aVersionInfoSize = GetFileVersionInfoSize (file.c_str(), &aVersionInfoSize);
	if (aVersionInfoSize) {
        	this->VersionInfo = new char [aVersionInfoSize];
        	if (GetFileVersionInfo (file.c_str(), 0, aVersionInfoSize, this->VersionInfo)) {
                	unsigned int aSize = 0;
                	VerQueryValue (this->VersionInfo, "\\", &(this->FixedInfo), &aSize);
		}
	}
}

FileVersion::~FileVersion() {
	delete this->VersionInfo;
}

unsigned short FileVersion::majorVersion () {
	if (!this->FixedInfo) {
		return 0;
	}
	VS_FIXEDFILEINFO *aInfo = (VS_FIXEDFILEINFO *) this->FixedInfo;
	return (aInfo->dwFileVersionMS >> 16);
}
                
unsigned short FileVersion::buildVersion () {
	if (!this->FixedInfo) {
		return 0;
	}
	VS_FIXEDFILEINFO * aInfo = (VS_FIXEDFILEINFO *) this->FixedInfo;
	return (aInfo->dwFileVersionLS);
}

int FileVersion::getVersion() {
	return StrToInt((String)this->majorVersion() + (String)this->buildVersion());
}
