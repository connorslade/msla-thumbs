#include <KPluginFactory>
#include <QImage>
#include <qimage.h>

#include "image.hpp"
#include "include/preview/lib.rs.h"
#include "msla_thumbs.hpp"

K_PLUGIN_CLASS_WITH_JSON(MslaThumbs, "../thumbnail.json")

MslaThumbs::MslaThumbs(QObject *parent, const QVariantList &args)
    : KIO::ThumbnailCreator(parent, args) {}
MslaThumbs::~MslaThumbs() {}

KIO::ThumbnailResult MslaThumbs::create(const KIO::ThumbnailRequest &request) {
  auto path = request.url().toLocalFile();
  auto image = extract_preview(path.toStdString());

  auto [width, height] = image->size();
  if (!width)
    return KIO::ThumbnailResult::fail();

  auto data = image->data().data();
  QImage img(data, width, height, width * 3, QImage::Format_RGB888);
  img = img.convertToFormat(QImage::Format_RGBA8888);
  removeBackground(img);

  return KIO::ThumbnailResult::pass(img);
}

#include "msla_thumbs.moc"
