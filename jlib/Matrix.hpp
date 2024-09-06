#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>

template<typename T>
class Matrix {
public:
    Matrix(size_t r, size_t c, T initial)
        : m_rows{r}, m_cols{c}, m_data(r*c, initial)
    {}

    template<typename Iterator>
    static Matrix copy_from(Iterator begin, Iterator end, size_t r, size_t c) {
        Matrix m(0, 0, 0);
        std::copy(begin, end, std::back_inserter(m.m_data));
        m.m_cols = m.m_data.size();
        m.m_rows = 1;
        m.resize(r, c);
        return m;
    }

    static Matrix move_from(std::vector<T>&& v, size_t r, size_t c) {
        Matrix m(0, 0, 0);
        m.m_data = std::move(v);
        m.m_cols = m.m_data.size();
        m.m_rows = 1;
        m.resize(r, c);
        return m;
    }

    void resize(size_t r, size_t c, T initial) {
        m_rows = r;
        m_cols = c;
        m_data.resize(r*c, initial);
    }
    void resize(size_t r, size_t c) {
        if (m_data.size() != r*c) {
            throw std::out_of_range(fmt::format(
                "new dimensions ({},{}) incompatible for current dimensions ({},{})",
                r, c, m_rows, m_cols
            ));
        }
        m_rows = r;
        m_cols = c;
    }

    void fill(T initial) {
        std::fill(m_data.begin(), m_data.end(), initial);
    }

    T* operator[](size_t offset) {
        return m_data.data() + offset*m_cols;
    }
    const T* operator[](size_t offset) const {
        return m_data.data() + offset*m_cols;
    }

    T& at(size_t r, size_t c) {
        if (r >= m_rows || c >= m_cols)
            throw std::out_of_range(fmt::format(
                "index ({},{}) out of range for dimensions ({},{})",
                r, c, m_rows, m_cols
            ));
        return m_data[r*m_cols+c];
    }
    T at(size_t r, size_t c) const {
        if (r >= m_rows || c >= m_cols)
            throw std::out_of_range(fmt::format(
                "index ({},{}) out of range for dimensions ({},{})",
                r, c, m_rows, m_cols
            ));
        return m_data[r*m_cols+c];
    }

    size_t rows() const {
        return m_rows;
    }

    size_t cols() const {
        return m_cols;
    }

private:
    size_t m_rows;
    size_t m_cols;
    std::vector<T> m_data;
};

#endif