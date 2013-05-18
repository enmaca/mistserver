#include "controller_basefiles.h"
#include "controller_storage.h"
#include <sys/stat.h>

///\brief Holds everything unique to the controller.
namespace Controller {
std::string BaseDir;
bool ValidDir;
void CheckFiles(JSON::Value & p) {

	if (Storage["config"]["basepath"].asString() != "") {
		BaseDir = Storage["config"]["basepath"].asString();
	} else {
		BaseDir = "/opt/mist/";
	}
	ValidDir = true;
	DIR * Dirp = opendir(BaseDir.c_str());
	struct stat StatBuf;

	if (!Dirp) {
		ValidDir = false;
	} else {
		dirent * entry;
		while ((entry = readdir(Dirp))) {
			if (stat((BaseDir + "/" + entry->d_name).c_str(), &StatBuf) == -1) {
				continue;
			}
			///Convert stat to string
			if( std::string(entry->d_name) !="." && std::string(entry->d_name) != ".."){
				p[std::string(entry->d_name)]=(int)StatBuf.st_size;
			}
		}
	}
}

}
