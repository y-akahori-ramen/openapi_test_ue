# Generate certificate files for development
rm *.pem

# Generate Private Key
openssl genrsa 2048 > private-key.pem

# Generate Certificate Signing Request
openssl req -new -key private-key.pem -out csr.pem -subj "/C=JP/ST=Yokohama/L=Yokohama/O=None/OU=None/CN=hoge/emailAddress=hoge"

# Generate self-signed certificate
openssl x509 -days 365 -req -signkey private-key.pem -in csr.pem -out crt.pem
