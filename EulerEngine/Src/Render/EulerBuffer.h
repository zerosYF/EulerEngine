#pragma once
#include"gkpch.h"
namespace EulerEngine {
	enum class ShaderDataType {
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static unsigned int ShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:		return 4;
		case ShaderDataType::Float2:	return 4 * 2;
		case ShaderDataType::Float3:	return 4 * 3;
		case ShaderDataType::Float4:	return 4 * 4;
		case ShaderDataType::Mat3:		return 4 * 3 * 3;
		case ShaderDataType::Mat4:		return 4 * 4 * 4;
		case ShaderDataType::Int:		return 4;
		case ShaderDataType::Int2:		return 4 * 2;
		case ShaderDataType::Int3:		return 4 * 3;
		case ShaderDataType::Int4:		return 4 * 4;
		case ShaderDataType::Bool:		return 1;
		}
		return 0;
	}
	struct BufferElement {
		std::string Name;
		ShaderDataType Type;
		unsigned int Offset;
		unsigned int Size;
		bool Normalized;
		BufferElement() {}
		BufferElement(ShaderDataType type, const std::string& name, bool normalized=false)
			:Name(name), Type(type), Offset(0), Size(ShaderDataTypeSize(type)), Normalized(normalized) {}

		unsigned int GetComponentCount() const{
			switch (Type) {
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Float2:	return 2;
			case ShaderDataType::Float3:	return 3;
			case ShaderDataType::Float4:	return 4;
			case ShaderDataType::Mat3:		return 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4;
			case ShaderDataType::Int:		return 1;
			case ShaderDataType::Int2:		return 2;
			case ShaderDataType::Int3:		return 3;
			case ShaderDataType::Int4:		return 4;
			case ShaderDataType::Bool:		return 1;
			}
			return 0;
		}
	};
	class BufferLayout {
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& element): m_Elements(element) {
			CalculateOffsetsAndStride();
		}
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		const std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		const std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
		inline const unsigned int GetStride() const { return m_Stride; }
	private:
		void CalculateOffsetsAndStride() {
			unsigned int offset = 0;
			m_Stride = 0;
			for (auto& element: m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		unsigned int m_Stride = 0;
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;
		static VertexBuffer* Create(float* vertices, unsigned int size);
	};
	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual unsigned int GetCount() const = 0;
		virtual void SetLayout(const BufferLayout& layout)= 0;
		virtual const BufferLayout& GetLayout() const = 0;
		static IndexBuffer* Create(unsigned int* indices, unsigned int count);
	};
}