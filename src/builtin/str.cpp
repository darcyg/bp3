#include "bp3/builtin/str.hpp"
#include "bp3/builtin/exceptions.hpp"

namespace bp3 {  namespace builtin {

bytes::bytes() : base(py_ptr::steal(PyBytes_FromString(""))) {}

bytes::bytes(object const & obj) :
    base(py_ptr::steal(PyObject_Bytes(obj.ptr().get())).raise_if_null()) {}

bytes::bytes(char const * s) :
    base(py_ptr::steal(PyBytes_FromString(s))) {}

bytes::bytes(std::string const & s) :
    base(py_ptr::steal(PyBytes_FromStringAndSize(s.data(), s.size()))) {}

bytes::operator std::string () const { return PyBytes_AS_STRING(ptr().get()); }

char const * bytes::c_str() const { return PyBytes_AS_STRING(ptr().get()); }

unicode::unicode() : base(py_ptr::steal(PyUnicode_FromString(""))) {}

unicode::unicode(object const & obj) :
    base(py_ptr::steal(
#if PY_MAJOR_VERSION == 2               
               PyObject_Unicode
#else
               PyObject_Str
#endif
               (obj.ptr().get())).raise_if_null()) {}

unicode::unicode(char const * s) :
    base(py_ptr::steal(PyUnicode_FromString(s))) {}

unicode::unicode(std::string const & s) : 
    base(py_ptr::steal(PyUnicode_FromStringAndSize(s.data(), s.size()))) {}

unicode::operator std::string () const {
    return bytes(py_ptr::steal(PyUnicode_AsUTF8String(ptr().get())));
}

str repr(object const & obj) {
    return str(py_ptr::steal(PyObject_Repr(obj.ptr().get())).raise_if_null());
}

}} // namespace bp3::builtin
