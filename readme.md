# turret_usd

This library, **turret_usd**, provides a `turretResolver` class, which overrides USD's `ArDefaultResolver`. This uses the functionality provided in [turret_lib](https://github.com/UTS-AnimalLogicAcademy/turret_lib) to talk to a [turret_server](https://github.com/UTS-AnimalLogicAcademy/turret_server) and allows custom URIs to be used within USD documents.

This is one of the projects which uses [turret_lib](https://github.com/UTS-AnimalLogicAcademy/turret_lib), the other being [turref_klf](https://github.com/UTS-AnimalLogicAcademy/turret_klf).  

## Building

We primarily support building with [rez](https://github.com/nerdvegas/rez) on Linux. However we do have prelimary support for windows and non-rez build systems.

For more information check out [building.md](building.md)

## Usage

### Environment Variables

**turret_usd** requires some environment variables to be set. These mainly depend on our rez contexts. 

 * `PXR_PLUGINPATH_NAME=C:/Users/142738/software/turret-usd/plugin/usd`
 * `PATH=%PATH%;C:/path/to/libzmq.dll;C:/path/to/turret-lib.dll`

### Windows

We only support running **turret_usd** on windows by having the **turret_server** running on a linux machine. Because of this you must specify the IP of the remote linux machine acting as a server.

 * `TURRET_SERVER_IP=172.22.15.55`

## Contributing
We use turret across almost every aspect of our USD pipeline and are constantly fixing bugs and finding time to improve turret more and more. We are however, very open to external pull-requests, and growing turret into a more versatile and robust piece of software with your help. Feel free to get in contact directly or through these GitHub repos. We'd love to talk! 
