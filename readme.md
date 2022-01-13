# readme

## run

```
docker volume create qmk
docker run --rm -it -v /c/qmk/mnt:/mnt/qmk -v qmk:/qmk qmkfm/qmk_cli:latest bash
```

First run:
```bash
python3 -m pip install qmk
qmk setup --home /qmk/qmk_firmware
qmk config user.keyboard=ferris/sweep
qmk config user.keymap=ryan-todd

mkdir -p /mnt/qmk/qmk_firmware/.build
ln -s /mnt/qmk/qmk_firmware/.build /qmk/qmk_firmware/.build

qmk new-keymap
mkdir -p /mnt/qmk/qmk_firmware/keyboards/ferris/keymaps
mv /qmk/qmk_firmware/keyboards/ferris/keymaps/ryan-todd /mnt/qmk/qmk_firmware/keyboards/ferris/keymaps/
ln -s /mnt/qmk/qmk_firmware/keyboards/ferris/keymaps/ryan-todd /qmk/qmk_firmware/keyboards/ferris/keymaps/ryan-todd
```

```bash
qmk compile
```
