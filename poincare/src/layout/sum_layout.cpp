#include "sum_layout.h"
#include "char_layout.h"
#include "horizontal_layout.h"

namespace Poincare {

const uint8_t symbolPixel[SumLayout::k_symbolHeight][SumLayout::k_symbolWidth] = {
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF},
  {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF},
  {0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
};

ExpressionLayout * SumLayout::clone() const {
  SumLayout * layout = new SumLayout(const_cast<SumLayout *>(this)->argumentLayout(), const_cast<SumLayout *>(this)->lowerBoundLayout(), const_cast<SumLayout *>(this)->upperBoundLayout(), true);
  return layout;
}

int SumLayout::writeTextInBuffer(char * buffer, int bufferSize, int numberOfSignificantDigits) const {
  return SequenceLayout::writeDerivedClassInBuffer("sum", buffer, bufferSize, numberOfSignificantDigits);
}

void SumLayout::render(KDContext * ctx, KDPoint p, KDColor expressionColor, KDColor backgroundColor) {
  // Computes sizes.
  KDSize upperBoundSize = upperBoundLayout()->size();
  KDSize lowerBoundSizeWithNEquals = HorizontalLayout(new CharLayout('n'), new CharLayout('='), lowerBoundLayout()->clone(), false).size();

  // Render the Sum symbol.
  KDColor workingBuffer[k_symbolWidth*k_symbolHeight];
  KDRect symbolFrame(p.x() + max(max(0, (upperBoundSize.width()-k_symbolWidth)/2), (lowerBoundSizeWithNEquals.width()-k_symbolWidth)/2),
      p.y() + max(upperBoundSize.height()+k_boundHeightMargin, argumentLayout()->baseline()-(k_symbolHeight+1)/2),
      k_symbolWidth, k_symbolHeight);
  ctx->blendRectWithMask(symbolFrame, expressionColor, (const uint8_t *)symbolPixel, (KDColor *)workingBuffer);

  // Render the "n=" and the parentheses.
  SequenceLayout::render(ctx, p, expressionColor, backgroundColor);
}

}
