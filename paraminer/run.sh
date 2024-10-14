wget  http://www.lamsade.dauphine.fr/~bnegrevergne/webpage/software/paraminer/paraminer-1.0.tar.gz
tar xzvf paraminer-1.0.tar.gz
rm paraminer-1.0.tar.gz
cd paraminer-1.0/ || exit
./configure
make
make install
./configure