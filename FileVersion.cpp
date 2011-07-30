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

unsigned short FileVersion::minorVersion () {
	if (!this->FixedInfo) {
		return 0;
	}
	VS_FIXEDFILEINFO *aInfo = (VS_FIXEDFILEINFO *) this->FixedInfo;
	return (aInfo->dwFileVersionMS);
}

unsigned short FileVersion::releaseVersion () {
	if (!this->FixedInfo) {
		return 0;
	}
	VS_FIXEDFILEINFO * aInfo = (VS_FIXEDFILEINFO *) this->FixedInfo;
	return (aInfo->dwFileVersionLS >> 16);
}

unsigned short FileVersion::buildVersion () {
	if (!this->FixedInfo) {
		return 0;
	}
	VS_FIXEDFILEINFO * aInfo = (VS_FIXEDFILEINFO *) this->FixedInfo;
	return (aInfo->dwFileVersionLS);
}

int FileVersion::getOFPVersion() {
	return StrToInt((String)this->majorVersion() + (String)this->buildVersion());
}

String FileVersion::getOFPMonitorVersion() {
        String major = (String)this->majorVersion();
        String minor = (String)this->minorVersion();
        String release = (String)this->releaseVersion();
        return major + "." + minor + release;
}

String FileVersion::getFullVersion() {
        String major = (String)this->majorVersion();
        String minor = (String)this->minorVersion();
        String release = (String)this->releaseVersion();
        String build = (String)this->buildVersion();
        return (major + "." + minor + "." + release + "." + build);
}
