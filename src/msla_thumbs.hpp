#pragma once

#include <KIO/ThumbnailCreator>

class MslaThumbs : public KIO::ThumbnailCreator
{
public:
    MslaThumbs(QObject *parent, const QVariantList &args);
    ~MslaThumbs() override;
    KIO::ThumbnailResult create(const KIO::ThumbnailRequest &request) override;
};
