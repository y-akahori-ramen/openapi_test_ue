gen-api:
	docker run --rm -v $(CURDIR):/local openapitools/openapi-generator-cli:v6.2.0 generate \
	    -i /local/api.yaml \
		-g cpp-ue4 \
		-o /local/ue/OpenAPITest/Plugins/Service/Source/OpenAPI \
		--additional-properties=unrealModuleName=OpenAPI
gen-dev-cert:
	docker build --file ./GenDevCertDockerfile . --tag openapitest_openssl:1.0 
	docker run --rm -v $(CURDIR)/cert:/local -w /local openapitest_openssl:1.0 /bin/bash ./generate.sh
run-swagger:
	docker run --name swagger -d -p 8080:8080  swaggerapi/swagger-editor
rm-swagger:
	docker rm -f swagger

.PHONY: gen run-swagger rm-swagger
