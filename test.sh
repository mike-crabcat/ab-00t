

for n in ~/data/geotron-blocks-triangulations/*.00t; do
  echo "testing $n"

  python3 ~/code/vulcan-kaitai/python/test.py $n >tmp-py
  ./build/tester $n >tmp-cpp

  sdiff tmp-py tmp-cpp
  if [ $? ]; then
    break
  fi
done
