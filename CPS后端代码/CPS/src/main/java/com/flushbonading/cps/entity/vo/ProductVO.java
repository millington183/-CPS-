package com.flushbonading.cps.entity.vo;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import io.swagger.annotations.ApiModel;
import io.swagger.annotations.ApiModelProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;


/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/20 18:36
 * @since 1.0.0
 */
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
@ApiModel(value = "ProductVO", description = "ProductVO对象")
public class ProductVO {
    /**
     * id号
     */
    @ApiModelProperty(value = "产品id号")
    @TableId(value = "id", type = IdType.AUTO)
    private Long id;
    
    /**
     * 物料牌号
     */
    @ApiModelProperty(value = "物料牌号")
    private String materialId;

    /**
     * 设备id
     */
    @ApiModelProperty(value = "设备id")
    private Integer equipmentId;


    /**
     * 包装人员
     */
    @ApiModelProperty(value = "包装人员")
    private String packagingWorkerName;

    /**
     * 压型人员
     */
    @ApiModelProperty(value = "压型人员")
    private String producerName;

    /**
     * 结果名
     */
    @ApiModelProperty("结果名")
    private String resultName;

    /**
     * 创建时间
     */
    @ApiModelProperty("创建时间")
    private String createTime;

}
