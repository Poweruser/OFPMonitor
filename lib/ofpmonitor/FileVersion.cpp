#include "FileVersion.h"

FileVersion::FileVersion(String file) {
        this->VersionInfo = NULL;
        int size = GetFileVersionInfoSize (file.c_str(), NULL);
	if (size > 0) {
        	this->VersionInfo = new char [size];
        	if (GetFileVersionInfo (file.c_str(), 0, size, this->VersionInfo)) {
                	unsigned int aSize = 0;
                	VerQueryValue (this->VersionInfo, "\\", &(this->FixedInfo), &aSize);
		}
	} else {
                this->FixedInfo = NULL;
        }
}

FileVersion::~FileVersion() {
        if(this->VersionInfo != NULL) {
        	delete this->VersionInfo;
                this->VersionInfo = NULL;
        }
}

unsigned short FileVersion::majorVersion () {
	if (!this->FixedInfo) { return 0; }
	VS_FIXEDFILEINFO *aInfo = (VS_FIXEDFILEINFO *) this->FixedInfo;
	return (aInfo->dwFileVersionMS >> 16);
}

unsigned short FileVersion::minorVersion () {
	if (!this->FixedInfo) { return 0; }
	VS_FIXEDFILEINFO *aInfo = (VS_FIXEDFILEINFO *) this->FixedInfo;
	return (aInfo->dwFileVersionMS);
}

unsigned short FileVersion::releaseVersion () {
	if (!this->FixedInfo) { return 0; }
	VS_FIXEDFILEINFO * aInfo = (VS_FIXEDFILEINFO *) this->FixedInfo;
	return (aInfo->dwFileVersionLS >> 16);
}

unsigned short FileVersion::buildVersion () {
	if (!this->FixedInfo) { return 0; }
	VS_FIXEDFILEINFO * aInfo = (VS_FIXEDFILEINFO *) this->FixedInfo;
	return (aInfo->dwFileVersionLS);
}

int FileVersion::getOFPVersion() {
	if (!this->FixedInfo) { return 0; }
	return StrToIntDef(IntToStr(this->majorVersion()) + (this->buildVersion() < 10?"0":"") + IntToStr(this->buildVersion()), 0);
}

String FileVersion::getOFPMonitorVersion() {
	if (!this->FixedInfo) { return "0"; }
        String major = (String)this->majorVersion();
        String minor = (String)this->minorVersion();
        String release = (String)this->releaseVersion();
        return major + "." + minor + release;
}

String FileVersion::getFullVersion() {
	if (!this->FixedInfo) { return "0"; }
        String major = (String)this->majorVersion();
        String minor = (String)this->minorVersion();
        String release = (String)this->releaseVersion();
        String build = (String)this->buildVersion();
        return (major + "." + minor + "." + release + "." + build);
}
