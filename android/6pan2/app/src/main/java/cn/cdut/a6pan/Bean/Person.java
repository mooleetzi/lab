package cn.cdut.sixpan.Bean;

public class Person {
    private long identity;//用户id
    private String name;//昵称
    private String countryCode;
    private String phone;
    private String email;
    private String createTime;//1970-1-1至今毫秒数
    private String createIP;
    private String icon;
    private Long spaceUsed;
    private Long spaceCapacity;
    private int type;//0普通用户，1管理
    private int status;//0正常，-10暂未登录
    private int version;
    private int ssid;//设备id

    public long getIdentity() {
        return identity;
    }

    public void setIdentity(long identity) {
        this.identity = identity;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getCountryCode() {
        return countryCode;
    }

    public void setCountryCode(String countryCode) {
        this.countryCode = countryCode;
    }

    public String getPhone() {
        return phone;
    }

    public void setPhone(String phone) {
        this.phone = phone;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getCreateTime() {
        return createTime;
    }

    public void setCreateTime(String createTime) {
        this.createTime = createTime;
    }

    public String getCreateIP() {
        return createIP;
    }

    public void setCreateIP(String createIP) {
        this.createIP = createIP;
    }

    public String getIcon() {
        return icon;
    }

    public void setIcon(String icon) {
        this.icon = icon;
    }

    public Long getSpaceUsed() {
        return spaceUsed;
    }

    public void setSpaceUsed(Long spaceUsed) {
        this.spaceUsed = spaceUsed;
    }

    public Long getSpaceCapacity() {
        return spaceCapacity;
    }

    public void setSpaceCapacity(Long spaceCapacity) {
        this.spaceCapacity = spaceCapacity;
    }

    public int getType() {
        return type;
    }

    public void setType(int type) {
        this.type = type;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public int getVersion() {
        return version;
    }

    public void setVersion(int version) {
        this.version = version;
    }

    public int getSsid() {
        return ssid;
    }

    public void setSsid(int ssid) {
        this.ssid = ssid;
    }
}
