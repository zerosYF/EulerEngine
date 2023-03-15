#include<tchar.h>
#include<string>
namespace EulerEngine {
	class EulerFile {
	protected:
		FILE *FileHandle;
		unsigned int openMode;
		TCHAR FileName;
		
	public:
		bool Open(const TCHAR *fileName,const TCHAR* openMode) {
			if (FileHandle) {
				fclose(FileHandle);
			}
			if (!fileName) {
				return false;
			}
			errno_t err = _tfopen_s(&FileHandle,fileName,openMode);
			if (err || !FileHandle)	{
				return false;
			}
			return true;
		}
		bool Write(const void* pBuffer,unsigned int size,unsigned int count) {
			if (!FileHandle) {
				return false;
			}
			if (!pBuffer||!size||!count) {
				return false;
			}
			fwrite(pBuffer,size,count,FileHandle);
			return true;
		}
		bool Read(void* pBuffer,unsigned int size,unsigned int count) {
			if (!FileHandle) {
				return false;
			}
			if (!pBuffer || !size || !count) {
				return false;
			}
			fread(pBuffer,size,count,FileHandle);
		}
		bool Flush() {
			int rtn = fflush(FileHandle);
			return rtn == 0;
		}
	};
}
