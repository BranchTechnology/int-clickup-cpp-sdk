##clickup-cpp-sdk example app

The library should be relatively self-explanatory however it could use some documentation. If additional features are needed pulling them in should be easy so feel free to or bug someone to. Note the return type is just nlohmann json atm and is not fully typed, so you'll need to in your client.

####Fetch content with a private repo:
Pulling a private git repo is surprisingly easy. Switching to ssh resolves the degeneracy issue with github moving away from user/password. Make sure your ssh keys are up to date and you should be good to go.

Notes:
- In this example it is referencing a specific tag like any public repo.
- In cicd make sure the runner or image has the appropriate key to pull.