# converter
a ebook converter


## Installation


## Development
### Required
- libepub-dev
- libhpdf-dev
- cmake 3.20 or later
- make 4.3 or later
- gcc-11 or later
- g++-11 or later
- python3
- OS: Debian11
  
```sh
# clone repository
git clone git@github.com:realjf/converter.git
cd converter


# install python3
sudo apt-get install python3 -y

# install required libraries
chmod +x ./scripts/setup.py
./scripts/setup.py -f ./scripts/libraries.json -d -b


```




