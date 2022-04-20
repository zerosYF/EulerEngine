namespace EulerEngine {
	template<typename T>
	class EulerSmartPointer {
	private:
		T* m_object;
	public:
		//ͨ��object�����ʼ��
		EulerSmartPointer(T* object) {
			m_object = object;
			if (m_object) m_object->IncreRef();
		}
		//ͨ���Զ���ָ���ʼ��
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
		//����ָ�������
		inline T& operator*() const {
			return *m_object;
		}//ȡָ��ָ��Ķ���;
		inline T* operator->() const {
			return m_object;
		}//ȡָ�뱾��;
		inline operator T*() const {
			return m_object;
		}//�Զ���ָ����ʽת��Ϊ��ָͨ�룻
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