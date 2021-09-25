package com.flushbonading.cps.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.flushbonading.cps.entity.Diary;
import com.flushbonading.cps.entity.vo.DiaryDataVO;
import com.flushbonading.cps.mapper.DiaryMapper;
import com.flushbonading.cps.service.DiaryService;
import com.flushbonading.cps.util.TimeQuantumUtil;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Map;

/**
 * <p>
 * 服务实现类
 * </p>
 *
 * @author zyx
 * @since 2021-06-09
 */
@Service
@Slf4j
public class DiaryServiceImpl extends ServiceImpl<DiaryMapper, Diary> implements DiaryService {
    /**
     * 每日每时刻生产量
     */
    @Autowired
    DiaryMapper diaryMapper;

    /**
     * 查询每一时段内的具体信息
     *
     * @return 返回时间段对应的
     */
    @Override
    public List<Map<String, Object>> queryDiary() {
        QueryWrapper<Diary> wrapper = new QueryWrapper<>();
        wrapper.select("time_id as time", "SUM(counts) as sum").groupBy("time_id");
        List<Map<String, Object>> maps = diaryMapper.selectMaps(wrapper);
        for (Map map : maps) {
            map.put("time", TimeQuantumUtil.getInstance().timeQuantum((Integer) map.remove("time")));
        }
        return maps;
    }

    @Override
    @Scheduled(cron = "59 59 23 * * ?")
    public Integer updateCounts() {
        log.info("******执行了定时任务");
        return diaryMapper.updateCounts();
    }

    @Override
    public List<DiaryDataVO> getDiaryDataVos() {
        List<DiaryDataVO> diaryDataVos = diaryMapper.getDiaryDataVos();
        TimeQuantumUtil timeQuantumUtil = TimeQuantumUtil.getInstance();
        for (DiaryDataVO diaryDataVO : diaryDataVos) {
            System.out.println(diaryDataVO);
            diaryDataVO.setName(timeQuantumUtil.timeQuantum(Integer.parseInt(diaryDataVO.getName())));
        }
        return diaryDataVos;
    }
}
