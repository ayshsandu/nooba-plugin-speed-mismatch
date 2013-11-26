#!bin/bash

git clone https://github.com/Asitha/nooba-plugin-speedmismatch.git

plugin_name="$1"

SPEEDMISMATCH="SPEEDMISMATCH"
speedmismatch="speedmismatch"
Speedmismatch="Speedmismatch"

PLUGIN_NAME="${plugin_name^^}"
plugin_name="${plugin_name,,}"
Plugin_name="${plugin_name^}"

mv ./nooba-plugin-speedmismatch $(echo "nooba-plugin-speedmismatch" | sed "s/$speedmismatch/$plugin_name/g") > /dev/null 2>&1

cd ./$(echo "nooba-plugin-speedmismatch" | sed "s/$speedmismatch/$plugin_name/g")

#changing directories
for i in 1 2 3; do
	for f in $(find -type d -not -path "*/.git*"); do

  		mv $f $(echo "$f" | sed "s/$SPEEDMISMATCH/$PLUGIN_NAME/g") > /dev/null 2>&1
  		mv $f $(echo $f | sed "s/$speedmismatch/$plugin_name/g") > /dev/null 2>&1
  		mv $f $(echo $f | sed "s/$Speedmismatch/$Plugin_name/g") > /dev/null 2>&1

	done
done

#changing filenames
for i in 1 2 3; do
	for f in $(find -type f -not -path "*/.git*"); do

  		mv $f $(echo $f | sed "s/$SPEEDMISMATCH/$PLUGIN_NAME/g") > /dev/null 2>&1
  		mv $f $(echo $f | sed "s/$speedmismatch/$plugin_name/g") > /dev/null 2>&1
  		mv $f $(echo $f | sed "s/$Speedmismatch/$Plugin_name/g")> /dev/null 2>&1
	done
done

#changing file content
for i in 1 2 3; do
	for f in $(find -type f -not -path "*/.git*"); do

  		sed -i "s/$SPEEDMISMATCH/$PLUGIN_NAME/g" $f > /dev/null 2>&1
  		sed -i "s/$speedmismatch/$plugin_name/g" $f > /dev/null 2>&1
  		sed -i "s/$Speedmismatch/$Plugin_name/g" $f > /dev/null 2>&1
	done
done

#restoring SPEEDMISMATCH keyword at the speedmismatch of the project library

sed -i "s/$PLUGIN_NAME = lib/$SPEEDMISMATCH = lib/g" $(echo "./SpeedmismatchPlugin/SpeedmismatchPlugin.pro" | sed "s/$Speedmismatch/$Plugin_name/g") > /dev/null 2>&1

#changing TARGET name
sed -i "s/TARGET = TestPlugin/TARGET = ${Plugin_name}Plugin/g" $(echo "./SpeedmismatchPlugin/SpeedmismatchPlugin.pro" | sed "s/$Speedmismatch/$Plugin_name/g") > /dev/null 2>&1


sudo chown $USER -R ./*
