use std::fs;

use common::serde::SliceDeserializer;
use ctb_format::File as CtbFile;
use goo_format::File as GooFile;

#[cxx::bridge]
mod ffi {
    extern "Rust" {
        type Image;
        fn size(&self) -> [u32; 2];
        fn data(&self) -> &[u8];

        fn extract_preview(path: String) -> Box<Image>;
    }
}

pub struct Image {
    width: u32,
    data: Vec<u8>,
}

fn extract_preview_inner(path: String) -> Option<Image> {
    let (_, ext) = path.rsplit_once(".")?;
    let data = fs::read(&path).unwrap();
    let mut des = SliceDeserializer::new(&data);

    match ext {
        "ctb" => {
            let file = CtbFile::deserialize(&mut des).ok()?;
            let mut image = Image::empty(file.large_preview.size().x);
            image.data = (file.large_preview.inner_data().iter())
                .flat_map(|x| x.as_slice())
                .copied()
                .collect();
            Some(image)
        }
        "goo" => {
            let file = GooFile::deserialize(&mut des).ok()?;
            let mut image = Image::empty(290);
            for pixel in file.header.big_preview.inner_data() {
                let red = ((pixel >> 11) & 0x1F) * 255 / 31;
                let green = ((pixel >> 5) & 0x3F) * 255 / 63;
                let blue = (pixel & 0x1F) * 255 / 31;
                image.data.extend([red, green, blue].map(|x| x as u8));
            }
            Some(image)
        }
        _ => None,
    }
}

pub fn extract_preview(path: String) -> Box<Image> {
    Box::new(extract_preview_inner(path).unwrap_or(Image::failed()))
}

impl Image {
    fn empty(width: u32) -> Self {
        Self {
            width,
            data: Vec::new(),
        }
    }

    fn failed() -> Self {
        Self::empty(0)
    }

    pub fn size(&self) -> [u32; 2] {
        [self.width, self.data.len() as u32 / self.width / 3]
    }

    pub fn data(&self) -> &[u8] {
        &self.data
    }
}
