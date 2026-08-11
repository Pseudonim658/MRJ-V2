# MRJ V2 — GitHub Actions Build

Push this project to GitHub. The workflow in `.github/workflows/build-firmware.yml`
builds the 14 `MRJ_*` display projects with PlatformIO and publishes each
`firmware.bin` as a separate GitHub Actions artifact.

No prebuilt `.bin` files are included in this source archive.
