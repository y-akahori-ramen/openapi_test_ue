gen:
	docker run --rm -v $(CURDIR):/local openapitools/openapi-generator-cli:v6.2.0 generate \
	    -i /local/api.yaml \
		-g cpp-ue4 \
		-o /local/ue/OpenAPITest/Plugins/Service/Source/OpenAPI \
		--additional-properties=unrealModuleName=OpenAPI
run-swagger:
	docker run --name swagger -d -p 8080:8080  swaggerapi/swagger-editor
rm-swagger:
	docker rm -f swagger

.PHONY: gen run-swagger rm-swagger
