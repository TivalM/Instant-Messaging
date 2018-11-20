package com.example.entity;

/**
 * Description: 用户信息类
 */
public class User {

    private String account;
    private String name;
    private String password;
    private int userId;

    public String getAccount() {
        return account;
    }

    public void setAccount(String account) {
        this.account = account;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public int getUserId() {
        return userId;
    }

    public void setUserId(int userId) {
        this.userId = userId;
    }

    @Override
    public String toString() {
        return "\nName:" + this.name +
                "\nId:" + this.userId +
                "\nAccount:" + this.account +
                "\nPassword" + this.password;

    }
}
