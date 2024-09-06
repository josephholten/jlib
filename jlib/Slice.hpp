template<typename T>
class Slice {
public:
    T const& operator[](size_t offset) const {
        return m_data[offset];
    }

    T& operator[](size_t offset) const {
        return m_data[offset];
    }

private:
    T* m_data;
    size_t m_size;
}