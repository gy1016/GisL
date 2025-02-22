/*!
 * @author tau
 * @date 12/29/20
 */

#include "rectangle.h"

namespace gisl {
Rectangle::Rectangle(OGREnvelope& envelope) : pmEnvelope(&envelope) {
  minX = pmEnvelope->MinX;
  maxX = pmEnvelope->MaxX;
  minY = pmEnvelope->MinY;
  maxY = pmEnvelope->MaxY;
}

void Rectangle::merge(const Rectangle& sOther) {
  minX = MIN(minX, sOther.minX);
  maxX = MAX(maxX, sOther.maxX);
  minY = MIN(minY, sOther.minY);
  maxY = MAX(maxY, sOther.maxY);
}

void Rectangle::merge(double dfX, double dfY) {
  minX = MIN(minX, dfX);
  maxX = MAX(maxX, dfX);
  minY = MIN(minY, dfY);
  maxY = MAX(maxY, dfY);
}

QPointF Rectangle::center() const {
  return {maxX / 2 + minX / 2, maxY / 2 + minY / 2};
}

QVector4D Rectangle::center4D() const { return QVector4D(center()); }

QRectF Rectangle::getQRectF() const {
  return {minX, maxY, maxX - minX, maxY - minY};
}
Rectangle::Rectangle(float minX, float maxX, float minY, float maxY) {
  this->minX = minX;
  this->minY = minY;
  this->maxX = maxX;
  this->maxY = maxY;
}
constexpr bool
Rectangle::inside(const std::pair<float, float>& p) const noexcept {
  return p.first < this->maxX && p.first > this->minX &&
         p.second < this->maxY && p.second > this->minY;
}
Rectangle::Rectangle() = default;
} // namespace gisl
