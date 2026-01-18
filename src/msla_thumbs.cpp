#include <KPluginFactory>
#include <QImage>

#include "msla_thumbs.hpp"

K_PLUGIN_CLASS_WITH_JSON(MslaThumbs, "../thumbnail.json")

MslaThumbs::MslaThumbs(QObject *parent, const QVariantList &args)
    : KIO::ThumbnailCreator(parent, args) {}
MslaThumbs::~MslaThumbs() {}

KIO::ThumbnailResult MslaThumbs::create(const KIO::ThumbnailRequest &request) {
  return KIO::ThumbnailResult::fail();
}

#include "msla_thumbs.moc"
