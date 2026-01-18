#include <KPluginFactory>
#include <QImage>
#include <qimage.h>

#include "include/previews/lib.rs.h"
#include "msla_thumbs.hpp"

K_PLUGIN_CLASS_WITH_JSON(MslaThumbs, "../thumbnail.json")

MslaThumbs::MslaThumbs(QObject *parent, const QVariantList &args)
    : KIO::ThumbnailCreator(parent, args) {}
MslaThumbs::~MslaThumbs() {}

KIO::ThumbnailResult MslaThumbs::create(const KIO::ThumbnailRequest &request) {
  auto path = request.url().toLocalFile();
  auto image = extract_preview(path.toStdString());

  auto width = image->width();
  if (!width)
    return KIO::ThumbnailResult::fail();

  auto height = image->data().length() / width / 3;
  QImage img(image->data().data(), width, height, QImage::Format_RGB888);

  return KIO::ThumbnailResult::pass(img);
}

#include "msla_thumbs.moc"
