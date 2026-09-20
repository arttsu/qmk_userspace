default:
    @just --list

compile:
    qmk compile -kb planck/rev6_drop -km arttsu

flash:
    qmk flash -kb planck/rev6_drop -km arttsu
