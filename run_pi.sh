#/bin/bash
python runner.py -bpi- -M300 -n500 -opi_300MeV  -d air_gap
python runner.py -bpi- -G1 -n500 -opi_1GeV  -d air_gap
python runner.py -bpi- -G3 -n500 -opi_3GeV  -d air_gap
python runner.py -bpi- -G10 -n500 -opi_10GeV -d air_gap
python runner.py -bpi- -G30 -n500 -opi_30GeV -d air_gap

python runner.py -bpi- -M300 -n500 -opi_300MeV   -g2 -d og_gap
python runner.py -bpi- -G1 -n500 -opi_1GeV  -g2 -d og_gap
python runner.py -bpi- -G3 -n500 -opi_3GeV  -g2 -d og_gap
python runner.py -bpi- -G10 -n500 -opi_10GeV  -g2 -d og_gap
python runner.py -bpi- -G30 -n500 -opi_30GeV  -g2 -d og_gap
