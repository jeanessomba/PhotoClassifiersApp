#pragma once

#include <QtCore>

#include "PhotoFactory.h"

class AlbumPresenter
{
public:
    explicit AlbumPresenter(const PhotoFactory &factory);

    void presentPhotoUnsorted()const;

private:
    PhotoFactory _factory;
};
