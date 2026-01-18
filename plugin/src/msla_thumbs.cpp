#include <KPluginFactory>
#include <QImage>

#include "msla_thumbs.hpp"
#include "include/previews/lib.rs.h"

K_PLUGIN_CLASS_WITH_JSON(MslaThumbs, "../thumbnail.json")

MslaThumbs::MslaThumbs(QObject *parent, const QVariantList &args)
    : KIO::ThumbnailCreator(parent, args) {}
MslaThumbs::~MslaThumbs() {}

KIO::ThumbnailResult MslaThumbs::create(const KIO::ThumbnailRequest &request) {
  auto path = request.url().toLocalFile();
  auto image = extract_preview(path.toStdString());

  return KIO::ThumbnailResult::fail();
}

#include "msla_thumbs.moc"
