namespace EulerEngine {
	template<typename T>
	class EulerSmartPointer {
	private:
		T* m_object;
	public:
		//通过object对象初始化
		EulerSmartPointer(T* object) {
			m_object = object;
			if (m_object) m_object->IncreRef();
		}
		//通过自定义指针初始化
		EulerSmartPointer(const EulerSmartPointer& pRef) {
			m_object = p->m_object;
			if (m_object) m_object->IncreRef();
		}
		~EulerSmartPointer() {
			if (m_object) {
				m_object->DecreRef();
				m_object = nullptr;
			}
		}
		//重载指针操作符
		inline T& operator*() const {
			return *m_object;
		}//取指针指向的对象;
		inline T* operator->() const {
			return m_object;
		}//取指针本身;
		inline operator T*() const {
			return m_object;
		}//自定义指针隐式转换为普通指针；
		inline EulerSmartPointer& operator=(T* object) {
			if (m_object != object) {
				if (m_object) m_object->DecreRef();
				if (object) object->IncreRef();
				m_object = object;
			}
			return *this;
		}
		inline EulerSmartPointer& operator=(const EulerSmartPointer& pRef) {
			if (m_object != pRef.m_object) {
				if (m_object) m_object->DecreRef();
				if (pRef.m_object) pRef.m_object->IncreRef();
				m_object = pRef.m_object;
			}
			return *this;
		}
		inline bool operator==(const EulerSmartPointer& pRef) const {
			return (pRef.m_object == m_object);
		}
		inline bool operator==(T* object) const {
			return (object == m_object);
		}
	private:
		inline void setObject(T* object) {
			m_object = object;
		}
		inline T* getObject() const{
			return m_object;
		}
	};
}