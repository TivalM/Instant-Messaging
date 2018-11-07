package com.example.controller;

import com.example.entity.HttpResponse;
import com.example.service.UserService;
import com.example.util.SystemConstant;
import org.springframework.beans.factory.annotation.Autowired;
//import org.springframework.stereotype.Controller;
//import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import javax.servlet.http.HttpSession;

/**
 * Description: 用户控制类
 * Date: 2018-11-06
 */

@RestController
public class UserController {

//    @RequestMapping(value = "/{user}")
//    public String Login(@PathVariable("user") int user, Model model) {
//        //把登录id传给jsp页面，便于建立WebSocket连接
//        model.addAttribute("user", user);
//        return "index";
//    }

    private UserService userService;

    @Autowired
    public void setUserService(UserService userService){
        this.userService = userService;
    }

    /**
     * 登录接口
     */
    @PostMapping("/login")
    public HttpResponse login(@RequestParam("account") String account,
                              @RequestParam("password") String password,
                              HttpSession session){
        int userId = userService.login(account,password);
        HttpResponse response;
        if(userId == SystemConstant.ACCOUNT_NOT_EXIST){
            response = new HttpResponse(SystemConstant.FAIL,"账号不存在","");
        }else if(userId == SystemConstant.PASSWORD_NOT_MATCH){
            response = new HttpResponse(SystemConstant.FAIL,"账号密码不匹配","");
        }else{
            response = new HttpResponse(SystemConstant.SUCCEED,"登录成功","");
        }
        // 将userId保存到session
        session.setAttribute("userId",userId);
        return response;
    }

    @PostMapping("/register")
    public HttpResponse register(@RequestParam("account") String account,
                                 @RequestParam("password") String password){
        return null;
    }


}
