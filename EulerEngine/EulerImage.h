#include<string>
#include<tchar.h>
namespace EulerEngine {
	class EulerImage {
	public:
		enum {
			IMAGE_BMP,
			IMAGE_TGA,
			IMAGE_DEFAULT,
		};
		unsigned int width;
		unsigned int height;
		unsigned int dataSize;
		unsigned char *data;
		unsigned char *palette;//��ɫ��

		bool Load(const TCHAR* fileName) {

		}
		bool LoadFromBuffer(unsigned char* pBuffer, unsigned int size) {
			// unsigned char* һ���ֽ�0~255 signed char һ���ֽ�-128~127
		}
		const unsigned char* GetPixel(unsigned int x, unsigned int y)const {

		}
	};
	class BMPImage :EulerImage{
	private:
		unsigned int enc;
		unsigned int planes;
		unsigned int ImgOffset;

		bool GetFile(const TCHAR* fileName) {
		}
		bool ReadBMPHeader() {
		}
		bool LoadBMPRaw() {
		}
		bool LoadBMPPalette() {
		}
		void FlipImg() {
		}
	};
	class TGAImage:EulerImage {
	private:
		unsigned int Enc;
		bool ReadHeader() {
		}
		bool LoadRawData() {
		}
		bool LoadTgaPalette() {
		}
		void BGR2RGB() {
		}
		void FlipImg() {
		}
	};
}
