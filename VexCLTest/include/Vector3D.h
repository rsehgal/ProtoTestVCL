#include <cstdlib>
#include <ostream>
#include <string>
#include <Global.h>
template <typename Type>
class Vector3D {

  typedef Vector3D<Type> VecType;

private:

  Type vec[3];

public:

  //VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_INLINE
  Vector3D(const Type a, const Type b, const Type c) {
    vec[0] = a;
    vec[1] = b;
    vec[2] = c;
  }

  //VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_INLINE
  Vector3D() {
    vec[0] = 0;
    vec[1] = 0;
    vec[2] = 0;
  }

  //VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_INLINE
  Vector3D(const Type a) {
    vec[0] = a;
    vec[1] = a;
    vec[2] = a;
  }

  //VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_INLINE
  Vector3D(Vector3D const &other) {
    vec[0] = other[0];
    vec[1] = other[1];
    vec[2] = other[2];
  }

  //VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_INLINE
  Vector3D& operator=(Vector3D const &other) {
    vec[0] = other[0];
    vec[1] = other[1];
    vec[2] = other[2];
    return *this;
  }


  /**
   * Constructs a vector from an std::string of the same format as output by the
   * "<<"-operator for outstreams.
   * @param str String formatted as "(%d, %d, %d)".
   */
  VECGEOM_CUDA_HEADER_HOST
  Vector3D(std::string const &str) {
    int begin = 1, end = str.find(",");
    vec[0] = std::atof(str.substr(begin, end-begin).c_str());
    begin = end + 2;
    end = str.find(",", begin);
    vec[1] = std::atof(str.substr(begin, end-begin).c_str());
    begin = end + 2;
    end = str.find(")", begin);
    vec[2] = std::atof(str.substr(begin, end-begin).c_str());
  }

  /**
   * Contains no check for correct indexing to avoid impairing performance.
   * @param index Index of content in the range [0-2].
   */
  //VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_INLINE
  Type& operator[](const int index) {
    return vec[index];
  }

  /**
   * Contains no check for correct indexing to avoid impairing performance.
   * @param index Index of content in the range [0-2].
   */
  //VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_INLINE
  Type const& operator[](const int index) const {
    return vec[index];
  }

  //VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_INLINE
  Type& x() { return vec[0]; }

  //VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_INLINE
  Type const& x() const { return vec[0]; }

  //VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_INLINE
  Type& y() { return vec[1]; }

  //VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_INLINE
  Type const& y() const { return vec[1]; }

  //VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_INLINE
  Type& z() { return vec[2]; }

  //VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_INLINE
  Type const& z() const { return vec[2]; }

  //VECGEOM_CUDA_HEADER_BOTH
  void Set(Type const &a, Type const &b, Type const &c) {
    vec[0] = a;
    vec[1] = b;
    vec[2] = c;
  }

  //VECGEOM_CUDA_HEADER_BOTH
  void Set(const Type a) {
    Set(a, a, a);
  }

  /// \return the length squared perpendicular to z direction
  //VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_INLINE
  Type Perp2() const {
    return vec[0]*vec[0]+vec[1]*vec[1];
  }

  /// \return the length perpendicular to z direction
  //VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_INLINE
  Type Perp() const {
    return Sqrt(Perp2());
  }

  /// Normalizes the vector by dividing each entry by the length.
  /// \sa Vector3D::Length()
  //VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_INLINE
  void Normalize() {
    *this /= Mag();
  }

  ///The dot product of two Vector3D<T> objects
  /// \return T (where T is float, double, or various SIMD vector types)
  //VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_INLINE
  static
  Type Dot(Vector3D<Type> const &left, Vector3D<Type> const &right) {
    return left[0]*right[0] + left[1]*right[1] + left[2]*right[2];
  }

  /// The dot product of two Vector3D<T> objects
  /// \return T (where T is float, double, or various SIMD vector types)
  //VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_INLINE
  Type Dot(Vector3D<Type> const &right) const {
    return Dot(*this, right);
  }
};
