#Run build.sh before

mkdir /usr/share/crcl-select -p
cp eww.yuck eww.scss /usr/share/crcl-select

mv crcl-* /usr/bin/

mkdir /etc/crcl-select -p
cp def_conf/toolbox.json def_conf/power_menu.json def_conf/theme.json /etc/crcl-select
