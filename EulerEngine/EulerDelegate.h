namespace EulerEngine {
	template<typename RTN,typename R1,typename R2>
	class EulerDelegate {
	public:
		typedef RTN(*Fnew)(R1,R2);
		typedef RTN(EulerDelegate::*Fthis)(R1,R2);
		Fthis TmpFuncPtr;
		Fnew WorkFuncPtr;
	public:
		EulerDelegate() {
			TmpFuncPtr = NULL;
			WorkFuncPtr = NULL;
		}
		template<class T>
		RTN CFunc(R1 r1,R2 r2) {
			return (*WorkFuncPtr)(r1,r2);
		}
		RTN Func(R1 r1,R2 r2) {
			return (*WorkFuncPtr)(r1,r2);
		}
		template<class T>
		void BindMemberFunc(void* p,Fnew f) {
			TmpFuncPtr = &EulerDelegate::CFunc<T>;
			WorkFuncPtr = f;
		}
		void BindNormalFunc(Fnew f) {
			TmpFuncPtr = &EulerDelegate::Func;
			WorkFuncPtr = f;
		}
		RTN Execute(R1 r1,R2 r2) {
			return (*this.*TmpFuncPtr)(r1,r2);
		}
	};
	
}
