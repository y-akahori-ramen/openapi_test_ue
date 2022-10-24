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
run-example-server:	
	docker compose -f ./exampleserver/docker-compose.yml up
stop-example-server:	
	docker compose -f ./exampleserver/docker-compose.yml stop
backup-example-server:
	docker compose -f ./exampleserver/docker-compose.yml run --rm maintenance tar cvf ./backup/${BACKUP_FILE} -C /usr/app/server/ saved
restore-example-server:
	docker compose -f ./exampleserver/docker-compose.yml down --volumes
	docker compose -f ./exampleserver/docker-compose.yml run --rm maintenance tar xvf ./backup/${BACKUP_FILE} -C /usr/app/server/
clean-example-server:
	docker compose -f ./exampleserver/docker-compose.yml down --rmi all --volumes --remove-orphans

.PHONY: gen-api gen-dev-cert run-swagger rm-swagger run-example-server stop-example-server backup-example-server restore-example-server clean-example-server
