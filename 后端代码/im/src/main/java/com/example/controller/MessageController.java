package com.example.controller;

import com.example.entity.HttpResponse;
import com.example.entity.Message;
import com.example.service.MessageService;
import com.example.util.SystemConstant;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.servlet.http.HttpSession;
import java.util.List;

/**
 * Description: 消息控制类
 * Date: 2018-11-06
 */

@RestController
public class MessageController {

    private MessageService messageService;

    @Autowired
    public void setMessageService(MessageService messageService) {
        this.messageService = messageService;
    }

    /**
     * 发起私聊
     *
     * @param targetId 对方ID
     */
    @PostMapping("/personChat")
    public HttpResponse makeChat(@RequestParam("targetId") int targetId, HttpSession session) {
        int userId = (int) session.getAttribute("userId");
        int result = messageService.makePersonSession(userId, targetId);
        if (result == 0) {
            return new HttpResponse(SystemConstant.FAIL, "新建会话失败", "");
        }
        return new HttpResponse(SystemConstant.SUCCEED, "新建会话成功", "");
    }

    /**
     * 获取历史消息
     *
     * @param chatSessionId 会话ID
     */
    @GetMapping("/historyMessage")
    public HttpResponse getHistoryMessage(@RequestParam("chatSessionId") int chatSessionId) {
        List<Message> messages = messageService.listHistoryMessage(chatSessionId);
        return new HttpResponse(SystemConstant.SUCCEED, "", messages);
    }

    /**
     * 获取离线消息
     *
     * @param chatSessionId 会话ID
     */
    @GetMapping("/offlineMessage")
    public HttpResponse getOfflineMessage(@RequestParam("chatSessionId") int chatSessionId) {
        List<Message> messages = messageService.listOfflineMessage(chatSessionId);
        return new HttpResponse(SystemConstant.SUCCEED, "", messages);
    }
}
