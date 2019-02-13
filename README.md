# Turret-USD

This library, **turret-usd**, provides a `turretResolver` class, which overrides USD's `ArDefaultResolver`. This uses the functionality provided in **turret-lib** to talk to a **turret-server** and allows custom URIs to be used within USD documents.

This is one of the example projects which uses **turret-lib**, the other being **turref-klf** (katana).  

## Usage

### Environment Variables

Turret-USD requires some environment variables to be set. These mainly depend on our rez contexts. 

 * PXR\_PLUGINPATH\_NAME=C:/Users/142738/software/turret-usd/plugin/usd
 * PATH=%PATH%;C:/path/to/libzmq.dll;C:/path/to/turret-lib.dll

### Windows

We only support running **turret-usd** on windows by having the **turret-server** running on a linux machine. Because of this you must specify the IP of the remote linux machine acting as a server.

 * TURRET_SERVER_IP=172.22.15.55
