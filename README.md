# msla-thumbs

A KDE plugin that adds thumbnail support for the `.goo` and `.ctb` sliced MSLA formats.
It just shows the embedded preview images.
The format implementations from my [mslicer](https://github.com/connorslade/mslicer) project are used.

<img width="2040" height="610" alt="msla-thumbs-preview" src="https://github.com/user-attachments/assets/6bc95eca-04dd-4ad1-a209-df633aeb2d82" />

## Installation

First you will need to register the `.goo` and `.ctb` formats on your system.
Download the XML files in [dist](dist) and [register them](https://unix.stackexchange.com/a/564888) on your system.

Next, download `msla-thumbs.so` from the latest release and copy it to `/usr/lib64/qt6/plugins/kf6/thumbcreator/`.
If using the Dolphin file browser, you will need to enable showing 'Sliced MSLA previews' in Configure › Interface › Previews.

## Development

Make sure the Rust crate (previews) is built first (in release mode).
Then the KDE plugin can be built with kde-builder.
